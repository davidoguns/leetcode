import sys
import json

# https://docs.python.org/2/library/json.html#json.dumps
# examine the decoders section for the container types
def key_value_extract_2(root, key_prefix, output_dict):
    if type(root) == list:
        for index, value in enumerate(list(root)):
            key_value_extract_2(value, "%s_%d" % (key_prefix, index), output_dict)
    elif type(root) == dict:
        for key, value in dict(root).items():
            key_value_extract_2(value, "%s_%s" % (key_prefix, key), output_dict)
    else:
        # if json values like "true" or "false" need conversion, numbers of dates need formatting
        # this is where further type inspection should inspect and make the decision
        output_dict[key_prefix] = root

# https://docs.python.org/2/library/json.html#json.dumps
# examine the decoders section for the container types
def key_value_extract(root, key_prefix, output_dict):
    if type(root) == list:
        output_dict[key_prefix] = ", ".join(root)
    elif type(root) == dict:
        for key, value in dict(root).items():
            key_value_extract(value, "%s_%s" % (key_prefix, key), output_dict)
    else:
        output_dict[key_prefix] = root

data = json.load(sys.stdin)
d = {}
key_value_extract_2(data, "root", d)


for column_name, value in d.items():
    print("%s = %s" % (column_name, value))


# key_value_extract_2 flattens arrays/lists with unique column names so
# item_list_0 = apple; item_list_1 = ball; item_list_2 = watch ... and so on
# key_value_extract will stop "descending" into objects when it sees a list
# and comma separate each item
