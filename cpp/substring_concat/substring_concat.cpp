#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

template <class T>
void print_list(const vector<T> &vec)
{
  for(const T &i:vec)
  {
    cout << i << endl;
  }
}

// https://leetcode.com/problems/substring-with-concatenation-of-all-words/description/
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> ret;
        if (words.empty()) {
            return vector<int>{}; //no words to find
        }
        if ((words.at(0).length() * words.size()) > s.length()) {
            return vector<int>{}; //string is too small to contain all substrings even once
        }

        //build word -> word_count map
        unordered_map<string, int> wordmap;
        for (auto words_itr = words.begin(); words_itr != words.end(); words_itr++) {
            auto entry = wordmap.find(*words_itr);
            if (entry != wordmap.end()) {
                entry->second += 1;
            }
            else {
                wordmap[*words_itr] = 1;
            }
        }
        //now we can work
        const size_t word_length = words.at(0).length();
        const size_t last_possible_start = s.length() - (word_length * words.size()) + 1;

        for (size_t start_char_index = 0; start_char_index < last_possible_start; ++start_char_index) {
            //copy map (how expensive?)
            unordered_map<string, int> wordmap_copy{wordmap};
            bool full_consume = true;
            for (size_t wc_index = 0; wc_index < words.size(); ++wc_index) {
                auto word_candidate = s.substr(start_char_index + (wc_index * word_length), word_length);
                auto word_found = wordmap_copy.find(word_candidate);
                //if word is found in map
                if (word_found != wordmap_copy.end()) {
                    word_found->second -= 1; //decrement value
                }
                else {
                    //if not found in map, then early exit this outer loop
                    goto next_start_letter;
                }
            }
            for (auto entry:wordmap_copy) {
                //means we either overdecremented a value past zero, or haven't decremented a value to zero yet
                full_consume = full_consume && entry.second == 0;
            }
            if (full_consume) { 
                ret.push_back(start_char_index);
            }
next_start_letter:;
        }
       return ret;
    }
};

int main(int argc, char* argv[]) {
    Solution s;
    vector<string> words = vector{string{"foo"}, string{"bar"}};
    string str{"barfoothefoobarman"};
    cout << "Solution #1" << endl;
    print_list(s.findSubstring(str, words));

    vector<string> words2 = vector{string{"foo"}, string{"bar"}, string{"the"}};
    cout << "Solution #2" << endl;
    print_list(s.findSubstring("barfoofoobarthefoobarman", words2));

    vector<string> words3 = vector{string{"word"}, string{"good"}, string{"best"}, string{"good"}};
    cout << "Solution #3" << endl;
    print_list(s.findSubstring("wordgoodgoodgoodbestword", words3));

    vector<string> words4 = vector{string{"word"}, string{"good"}, string{"best"}, string{"word"}};
    cout << "Solution #4" << endl;
    print_list(s.findSubstring("wordgoodgoodgoodbestword", words4));

    string long_string{"cxksvbkmmlkwviteqccjhsedjmoyimskmeehhovubiszsodiqhtyaxdlktmuiggukldubzqdjiebyjkpqfpqdsepmqluwrqictcguslddphdyrsowjhbcnsqddmbvclzvqhsksxnhethvnyuxfxzsqpxvdasflscbzumssbbwuluijqhqngkfxhdahvhunjwpgkjylmwixssgizyyhifepigyenttyriebtcogbwftqmcpmcwvhcmsklyxgryxccyvhodiljbbxftjhrerurleejekacheehclvfviqxmnefzowdhswsxcbdmdfvilekzcrukityxyfwmcctwanvdoyptfnbtrnsthoepieoiklwmppkpegssgknmxpfoezilnocxsrfcebqtsdkwjfqppedmvkczjmnzcpwxiebofujyxuwgzpxotdcqnerzteyvwwseauvgoeglyctzrspmvrcjyuiraimwehdfbalretcfxxeppwdnniwnegeeotdsaixdikuodytbxasmwxzlfxzldfstaxmcflfpybdbzzewzylxwmidkjrprjjtgxwnideifjkeiqdjpogncrsmcjetsnnamlpwotftdranhdxytfnvwgkzroukdjmpucnjxscajcqtfptaujwtrguiwouzyhqulddiygjjkbesqyskjofawzisqdrqkjkvnodlwowgrbyhzruihzkezsyrvshhbreqhkbfaymsbmzaftkpvutwotnklutnnydxihcihqcidckkxwzssuogodszzmopmumwbogkhjukleukcufuqvcezxgylunxobvrsbbzkvlxbhiddnzuieyhbeimbxlpzghthksugdrjkznoomkzsiitpqhqquhraqkkbcgjhxstzhjpwtoocxirprjfmqwmhgyikgtrellftwupqldsinlzfwfrmdfvmgfwmyqsmdxhzuwpfbjprwowsvphzuelckjrkbjwejdgdbxkdhzwfnsaljjkdnxixizikigqrmwwnugsdhokxikirtuxjtfibgslozeilagywptbwhmvqwdjszgbsnjutchkdluooaompjooraljypusobvjohdklmuqyogoquaigqwxsjiryclpfjywsdgdpctpqzdivgqbwoapykiypvpuepswsybkcwzsxfbvntylibcglmeciuzojrnesqounppmwshjlgxtjzzumgzwcymlpbrjsfehxtttldfwlcsudrqpzpnbnapfbgovoucnnygadnzqrrkvkckkuanjaeodnfzbzdqpdypgmoydhiysnlehnrsnwjsloropxeeacwjomhuusuohhsqulihjrcuhvixsmdvpbefqnbmhwaodueafnjpellmhulbiqwzscfiqiuxgwomqsmxfvmmhyaqunrcdocvqjfirbiyzwmpoypwtdkcdksxzkacaeasnhbgjlgkhsaxqrvmufoyrjxqvztxdvpscszndfymaamqrhelnvleejxbiqyonpgpihdnpbcpbohuvmfkhtrncoqmgqatfjkpqnffqjutxenuqvhzoyosogeuwhpdqzvipaofjkbiooeejlfzjvrzbytxhidxkyfzavglghtuyzbhlgjwcawdardhcigmgonijvtpdokdnlmatvzxyvdymggqqmcyargmnbbqpnveahhudgtbdwzrehiuwmsyeykrbojqbexelgaomtrrqtiucspyfhxjijajxjcbpbfahfrvyimodwjgpyewhdfrphbmsfnhguhpzakalyoowzunzbjhgqyvxbkrgzyouidtinttnkkkjezjhjsqbslzuvqcvrrrzwkjkgdzsnldtlmdwgtxzewvcpxzgqqhncqzkvackmgexujtbcqcipxmgwlopdvcgndqjdvtpbzoxijamacvrzjxyvnnykpgxuxixucpvddumpvapxxizhhxeukcebjdvimucqjztpvheqivqfdpokosgyxkbipwsbqurcvltquzjcwzkzqyletteqffaubswtonxjasbvrkznljodkbhfunvzsxwvpsrdhqokjpfcceqnqgrckaheoegibceqwvvdljnwyuzcbrsrxlthlcobgwkhyqzwlubyfrvflwimnafknauacickeoteeucrodrvuobikjwxlckyeeyjoctusnawhcpyfhtcvukifgfskpspvrylvtfogfmqhcqpjlrgidopjwiunalltjwpccflhrdrvtgegznocdgnzohposakdwbgagtkxwbtrjzxkoomuuzvkjkadkkhjlpjtittewoxfpwpemdygftsqgttqfcbtrlmbefhbteijbapnfpwkkqcslwjramkuxyveeffzlpkopbevsahdskveigvivhesfcwlhdnstxhkblhtnpyfbwljegrzpysxaqihwxzrxibyvjriasqbobmskfsbdmydejkagmrdutdqevagpsjduvxgarhefihkrukzgcdcxguddvlsnuxjrxrrozvuhfgazqzhuejtlgyqdllsfiewhvqwunsdsydtqfanjmiwujpxuapcktysrqoleirwiwsabupngajcjyzdarflmgddwtradizletninfvwfgyohathrbsdhxjfsaivkjiqcyypdvniemylmrufspkbmthhvpcfanwclwtouhwavunjnhogwyhluqsphwxhjvjutfkpoipjecusmiaiijvcapujmrrxocshhexxnmgrraldklntxlxzarimkzkyceglkfjxtrrkucpeqfznqxmqqufbwrbaxhnhoyfiqwumakqsrsfhrtzhqekoxmouvdckchsufmghyyarqhyhbartebhenxylaavcjnwobeycdytthudiuudavkeljdwkdtopindjrdnudjqlftvznzbklgxvlthqmvfuklgcovysgodlhakwzmjnugifcpvqmbnzovdcqbwzsbkbcvydjhqdpakrphkeixdwuibmjxlbzwddtdgcmxhbxtvpafvleajyikkrkyvluaondwrptastvnivufiafsanengqldbfdrugonxjnqckfkfcrocwiflosufdxikbaejqthzgzcqeoxggnlexqqmkktpjbzkbfwtydtgcvyilxrrlewkwowgapvjruwubsozxjhzgfjrcalpejaazyizodihzedaytbveiwkpgesgphnajpziyyybihdpkfnghlkrhvhnzbwqkjquareyrcczjfqvkebtpmnyjwmkxkajvsfvljucnwbybsunyxjplwnusbgrlicgaieltynjwrhzlbmlzvamtphntngeyjnytrmorbxnufmfiasjwswrkdfdsljqwwrppfgggdtdkhktidcgxyxhdcmyqwqosjekomqxpmaatkvbpxhnyhwdljdbfuszfwjukctzovbjhwnxwwkwdgzppdswzkweihasjtuzoxjywwvsuhoynppfujdvwzaghcbsyxsoubmqzhitoyteqklmwoisqkaxmbpkyhztklllvwhjuapmnazjrhbhrbgffvqdfryrckdzgkjcmapzdqiuzldspjxugpxlgydliikouvsgyjgbzqxacasrjslphkdqiidsqniklbsjkymmpjmtlfkuxxlghowsyzkopvaawtlitzukijdtqppnoavyrsqptcgixgkvbxgxwcjglpzbeqqvrmtigjzbnfknowkrwqostybgnaktraokohuwstyibkvpihgeyxztvabkcldvosfcbbbuxzcajzptgxygwzbrzddbohzcbgheiiyhhchsdylmvlsukuljxrnnymqbsxfchgjoksiqqtcohwirqvdpmsfmevpyuxbbdmrpfzfvujldgtvypaqdsvqwsfwoczrhmiztjgqfqcjyvewmeoqwjiudnqrssizesazdhpjxrsxpytdektctbwzroslgbmmvnlzubitucqjalnevigrmeqfuiqblcnhrbilcqgyuwiukxafhgwtmoagxqhkvxtmabaetgcnfkjpjjurrtmdhnkgfttasmpuqpyjxbzcnirxsoojjcpspbbvuuxpimjydikbjjdwrxvlnlvwokqflrchlaywokussetdnybhxzsmkpkybbgosiwgiwcxgwradmfsmhzkguwsjhtlizbchziswmrcjifowkgitisbcrunanakocmxbxpxjicushiotpxnxrobikoixpunrhlsgcsrlwmdfusylplkgclrmcbkrwzkfkelnyeyuqdznvyamllvnymacnmvllfqymdlkilfaognmgqysbvfbjhextbkhhdftgsfqdmrttgfbwgtzdbdnijmekwntzsoikuypiridaqfyyaybbdommasyxfsyxggjchylyiqayvzywxazcolordookgmhpvstcqgcbxdzseaqbaqfqdvhjjvtqkbhhtajmhnneqoyuopxqhehkzotjmnbyqiflkoztdmzwdaqtpqkyuriwhefvtgtjqywcowyskxonxghoytovmxrtdypwgihyjdazzytkyjzxqioqbcnnbgheeyakihitnltmlmyjwyjogxeizuxbaghfeirprcienbtyqrkmrvaasgktchwdoekuobjffsmsvftlyfxqazquiankjkpxozucddjixxdtcweddevffnznpoayypyopssuxecxbfqgdwjgaglgtmvibvibngseakyaqaxuipalllsorfwksrutpcuelminzgnriklqzlcnwwbpbxzvqvohylllztyaboskadccrgppcsfgrgbhcsrcfcngynhbbbncgqexyvpbnujeamneeegljtsjhbkkcamissiqnxrarcetpsyvyehhabqjcbtgdiovawlqtfqmhxgwrgupmdxoepxistovdeqfdcvyhmloltnczhrnkqcqgzayuquxumfzoayxolozeddfkxswnuovwowqeqqaevctxasmlgnpjrwvootdjhzhxvzdnpgrmimmifavnnkxgiuwwoahxbovwqalhgcworiwyitlxdkenfakvatsbkpzaqkhwpdnillgvfrtkexyjzigcdydnqfpgrxegcroqduliogssfqdfalhglmtbrjjjiormhgckcqsswnmcfrhgcqoochrusbfcrwpyerjjhdbgsqiyhrgmhucjdtfwwmanjpopjxasceyvugvdzbpgvtsapxwlkzbvopmxonqsrqplxkqwlgfibxjquheggfdxwqwmfoewfujegzcuhhclenbbxfjfmncifbumpbiuxtadudxekcprrquqyfwksatzbpltsvnpqovltspdwgwqysgwyehsfcsitfbmdrdthygatxfrdchcuoysshlzlfifmltpcyljxrlsprjuttwpjxkbexdsenzqysidqtopmajbrvwmoudxrpaymdqsspjtjtwbomtameefzctpwxoqmpobugtnxeiizelnqeofjskkugasdoirfyucgqpfuznudzjvfxaqrnbntdiyrqrzrmbxcsdyrsuwterzdurxjskcvscpltqchrbjlgkczgyumrtqlnnufzyduauhwklddmpotbsuhsoulkmxxbtcauhwwbdsnqysdniyoasvugrgqdfneashubftdjnsblneyvcoyumsddatjhjnidueeaxjllemyrtxmxnkszfxfhqopbbxeydladunoybopwlcubooavlfddvsfxrlxuwzxrmnrpchmpliqbwtxhyckuuptldshzrfsfukwwtiogqehoxgvyigucxppahzcygwfaibzbmnjetrttzoriwnmucewldaljxqjfrkjdxsitldmlrfvoshkwnghqhszgilnbvwhvrroeuaplhmbzulxhueabybjimwjkvqhmjvqdxireuufqgcaaiadgbmoqkzafshtbemhduahquohasjcajfimryccxejpndtrpcwlcdbwtkzltbnchxpavtevyqmltffkjbvlhwkajjocmdhvbywyrctpsidnpixzlsksrwvaflcuojprhlqbqlqivtwldtkpowjftefaphugtkxcxpdndwyyrujvpvmdsxklcpntzibusbwpqcdvybupxfmobautyegcwtxvbzpvanlspqoptkhspviswclwjtafnxcqytmaiztarjpmtygkuodstqockqjznnpmgdmqehqxqgjlgrwagbuzrkdbaocobscjxqzeyqbqynegechmddnuosyogaejuiuuzuyzmzrmovutxbfchvzvnzjuzqfwyaqxwqykrqygnsznwgpddoyrnjnpzsnysdxqvyamqysdttqpcgsfwswkbjzdemdyrcpoaraqstulomcquuwroudrgcumqzkjcbxctzvlsryhdazawxrksubayy"};
    vector<string> words5 = vector{string{"otftdranhdxytfnvwgkzroukdj"},string{"iflkoztdmzwdaqtpqkyuriwhef"},string{"lbsjkymmpjmtlfkuxxlghowsyz"},string{"cddjixxdtcweddevffnznpoayy"},string{"snjutchkdluooaompjooraljyp"},string{"fuszfwjukctzovbjhwnxwwkwdg"},string{"frmdfvmgfwmyqsmdxhzuwpfbjp"},string{"ukityxyfwmcctwanvdoyptfnbt"},string{"mhnneqoyuopxqhehkzotjmnbyq"},string{"vtgtjqywcowyskxonxghoytovm"},string{"wouzyhqulddiygjjkbesqyskjo"},string{"mfiasjwswrkdfdsljqwwrppfgg"},string{"zruihzkezsyrvshhbreqhkbfay"},string{"rsxpytdektctbwzroslgbmmvnl"},string{"jdwrxvlnlvwokqflrchlaywoku"},string{"xhnhoyfiqwumakqsrsfhrtzhqe"},string{"gtbdwzrehiuwmsyeykrbojqbex"},string{"tpcyljxrlsprjuttwpjxkbexds"},string{"tsjhbkkcamissiqnxrarcetpsy"},string{"keiqdjpogncrsmcjetsnnamlpw"},string{"rquqyfwksatzbpltsvnpqovlts"},string{"tdgcmxhbxtvpafvleajyikkrky"},string{"qvrmtigjzbnfknowkrwqostybg"},string{"vluaondwrptastvnivufiafsan"},string{"rnsthoepieoiklwmppkpegssgk"},string{"cyypdvniemylmrufspkbmthhvp"},string{"ihcihqcidckkxwzssuogodszzm"},string{"chrusbfcrwpyerjjhdbgsqiyhr"},string{"wmeoqwjiudnqrssizesazdhpjx"},string{"ommasyxfsyxggjchylyiqayvzy"},string{"kwntzsoikuypiridaqfyyaybbd"},string{"cwjomhuusuohhsqulihjrcuhvi"},string{"wxazcolordookgmhpvstcqgcbx"},string{"nusbgrlicgaieltynjwrhzlbml"},string{"xrtdypwgihyjdazzytkyjzxqio"},string{"xfvmmhyaqunrcdocvqjfirbiyz"},string{"fuklgcovysgodlhakwzmjnugif"},string{"hzhxvzdnpgrmimmifavnnkxgiu"},string{"xsmdvpbefqnbmhwaodueafnjpe"},string{"xfbvntylibcglmeciuzojrnesq"},string{"cnhrbilcqgyuwiukxafhgwtmoa"},string{"xkajvsfvljucnwbybsunyxjplw"},string{"zuieyhbeimbxlpzghthksugdrj"},string{"gbzqxacasrjslphkdqiidsqnik"},string{"jxtrrkucpeqfznqxmqqufbwrba"},string{"chziswmrcjifowkgitisbcruna"},string{"jyzdarflmgddwtradizletninf"},string{"pcktysrqoleirwiwsabupngajc"},string{"dkenfakvatsbkpzaqkhwpdnill"},string{"kbiooeejlfzjvrzbytxhidxkyf"},string{"wlopdvcgndqjdvtpbzoxijamac"},string{"xsoojjcpspbbvuuxpimjydikbj"},string{"faubswtonxjasbvrkznljodkbh"},string{"uqsphwxhjvjutfkpoipjecusmi"},string{"nawhcpyfhtcvukifgfskpspvry"},string{"xkdhzwfnsaljjkdnxixizikigq"},string{"zxgylunxobvrsbbzkvlxbhiddn"},string{"alltjwpccflhrdrvtgegznocdg"},string{"gffvqdfryrckdzgkjcmapzdqiu"},string{"hzedaytbveiwkpgesgphnajpzi"},string{"wmpoypwtdkcdksxzkacaeasnhb"},string{"hsdylmvlsukuljxrnnymqbsxfc"},string{"bbbncgqexyvpbnujeamneeeglj"},string{"bjhgqyvxbkrgzyouidtinttnkk"},string{"pyuxbbdmrpfzfvujldgtvypaqd"},string{"cfanwclwtouhwavunjnhogwyhl"},string{"plkgclrmcbkrwzkfkelnyeyuqd"},string{"ugvdzbpgvtsapxwlkzbvopmxon"},string{"msbmzaftkpvutwotnklutnnydx"},string{"pdwgwqysgwyehsfcsitfbmdrdt"},string{"elgaomtrrqtiucspyfhxjijajx"},string{"biqyonpgpihdnpbcpbohuvmfkh"},string{"llmhulbiqwzscfiqiuxgwomqsm"},string{"mpucnjxscajcqtfptaujwtrgui"},string{"gdzsnldtlmdwgtxzewvcpxzgqq"},string{"gdtdkhktidcgxyxhdcmyqwqosj"},string{"zubitucqjalnevigrmeqfuiqbl"},string{"aymdqsspjtjtwbomtameefzctp"},string{"kjezjhjsqbslzuvqcvrrrzwkjk"},string{"zavglghtuyzbhlgjwcawdardhc"},string{"fawzisqdrqkjkvnodlwowgrbyh"},string{"vrzjxyvnnykpgxuxixucpvddum"},string{"rdutdqevagpsjduvxgarhefihk"},string{"ydhiysnlehnrsnwjsloropxeea"},string{"hgjoksiqqtcohwirqvdpmsfmev"},string{"jyxuwgzpxotdcqnerzteyvwwse"},string{"sozxjhzgfjrcalpejaazyizodi"},string{"usobvjohdklmuqyogoquaigqwx"},string{"tmdhnkgfttasmpuqpyjxbzcnir"},string{"quareyrcczjfqvkebtpmnyjwmk"},string{"rmwwnugsdhokxikirtuxjtfibg"},string{"qsrqplxkqwlgfibxjquheggfdx"},string{"rukzgcdcxguddvlsnuxjrxrroz"},string{"oomuuzvkjkadkkhjlpjtittewo"},string{"wqwmfoewfujegzcuhhclenbbxf"},string{"yjogxeizuxbaghfeirprcienbt"},string{"qbwoapykiypvpuepswsybkcwzs"},string{"lvtfogfmqhcqpjlrgidopjwiun"},string{"rwowsvphzuelckjrkbjwejdgdb"},string{"jfqppedmvkczjmnzcpwxiebofu"},string{"hygatxfrdchcuoysshlzlfifml"},string{"gxqhkvxtmabaetgcnfkjpjjurr"},string{"zppdswzkweihasjtuzoxjywwvs"},string{"hgyikgtrellftwupqldsinlzfw"},string{"kckkuanjaeodnfzbzdqpdypgmo"},string{"aiijvcapujmrrxocshhexxnmgr"},string{"sjiryclpfjywsdgdpctpqzdivg"},string{"kuxyveeffzlpkopbevsahdskve"},string{"uqvhzoyosogeuwhpdqzvipaofj"},string{"gjhxstzhjpwtoocxirprjfmqwm"},string{"cwiflosufdxikbaejqthzgzcqe"},string{"qeqqaevctxasmlgnpjrwvootdj"},string{"ymggqqmcyargmnbbqpnveahhud"},string{"ekomqxpmaatkvbpxhnyhwdljdb"},string{"zvamtphntngeyjnytrmorbxnuf"},string{"uhoynppfujdvwzaghcbsyxsoub"},string{"efhbteijbapnfpwkkqcslwjram"},string{"koxmouvdckchsufmghyyarqhyh"},string{"tthudiuudavkeljdwkdtopindj"},string{"nwwbpbxzvqvohylllztyaboska"},string{"dccrgppcsfgrgbhcsrcfcngynh"},string{"qdpakrphkeixdwuibmjxlbzwdd"},string{"ftgsfqdmrttgfbwgtzdbdnijme"},string{"ounppmwshjlgxtjzzumgzwcyml"},string{"cpvqmbnzovdcqbwzsbkbcvydjh"},string{"pbrjsfehxtttldfwlcsudrqpzp"},string{"qbcnnbgheeyakihitnltmlmyjw"},string{"ztvabkcldvosfcbbbuxzcajzpt"},string{"xfpwpemdygftsqgttqfcbtrlmb"},string{"hncqzkvackmgexujtbcqcipxmg"},string{"ilfaognmgqysbvfbjhextbkhhd"},string{"hvqwunsdsydtqfanjmiwujpxua"},string{"yqrkmrvaasgktchwdoekuobjff"},string{"egeeotdsaixdikuodytbxasmwx"},string{"jfmncifbumpbiuxtadudxekcpr"},string{"slozeilagywptbwhmvqwdjszgb"},string{"kkugasdoirfyucgqpfuznudzjv"},string{"pvapxxizhhxeukcebjdvimucqj"},string{"bqurcvltquzjcwzkzqyletteqf"},string{"cbrsrxlthlcobgwkhyqzwlubyf"},string{"mqzhitoyteqklmwoisqkaxmbpk"},string{"nbnapfbgovoucnnygadnzqrrkv"},string{"ztpvheqivqfdpokosgyxkbipws"},string{"auvgoeglyctzrspmvrcjyuirai"},string{"yhmloltnczhrnkqcqgzayuquxu"},string{"funvzsxwvpsrdhqokjpfcceqnq"},string{"vuhfgazqzhuejtlgyqdllsfiew"},string{"gmhucjdtfwwmanjpopjxasceyv"},string{"vpscszndfymaamqrhelnvleejx"},string{"dzseaqbaqfqdvhjjvtqkbhhtaj"},string{"zylxwmidkjrprjjtgxwnideifj"},string{"nzohposakdwbgagtkxwbtrjzxk"},string{"igvivhesfcwlhdnstxhkblhtnp"},string{"trncoqmgqatfjkpqnffqjutxen"},string{"vwfgyohathrbsdhxjfsaivkjiq"},string{"rdnudjqlftvznzbklgxvlthqmv"},string{"kopvaawtlitzukijdtqppnoavy"},string{"raldklntxlxzarimkzkyceglkf"},string{"nakocmxbxpxjicushiotpxnxro"},string{"wxoqmpobugtnxeiizelnqeofjs"},string{"smsvftlyfxqazquiankjkpxozu"},string{"fwksrutpcuelminzgnriklqzlc"},string{"nefzowdhswsxcbdmdfvilekzcr"},string{"ibvibngseakyaqaxuipalllsor"},string{"znvyamllvnymacnmvllfqymdlk"},string{"gcvyilxrrlewkwowgapvjruwub"},string{"mwehdfbalretcfxxeppwdnniwn"},string{"wwoahxbovwqalhgcworiwyitlx"},string{"nmxpfoezilnocxsrfcebqtsdkw"},string{"engqldbfdrugonxjnqckfkfcro"},string{"grckaheoegibceqwvvdljnwyuz"},string{"jcbpbfahfrvyimodwjgpyewhdf"},string{"rvflwimnafknauacickeoteeuc"},string{"gxygwzbrzddbohzcbgheiiyhhc"},string{"wcxgwradmfsmhzkguwsjhtlizb"},string{"bikoixpunrhlsgcsrlwmdfusyl"},string{"ssetdnybhxzsmkpkybbgosiwgi"},string{"vyehhabqjcbtgdiovawlqtfqmh"},string{"opmumwbogkhjukleukcufuqvce"},string{"vjriasqbobmskfsbdmydejkagm"},string{"gjlgkhsaxqrvmufoyrjxqvztxd"},string{"yyybihdpkfnghlkrhvhnzbwqkj"},string{"kznoomkzsiitpqhqquhraqkkbc"},string{"yhztklllvwhjuapmnazjrhbhrb"},string{"jjiormhgckcqsswnmcfrhgcqoo"},string{"rphbmsfnhguhpzakalyoowzunz"},string{"igmgonijvtpdokdnlmatvzxyvd"},string{"rsqptcgixgkvbxgxwcjglpzbeq"},string{"zldspjxugpxlgydliikouvsgyj"},string{"enzqysidqtopmajbrvwmoudxrp"},string{"naktraokohuwstyibkvpihgeyx"},string{"zlfxzldfstaxmcflfpybdbzzew"},string{"mfzoayxolozeddfkxswnuovwow"},string{"rodrvuobikjwxlckyeeyjoctus"},string{"yfbwljegrzpysxaqihwxzrxiby"},string{"croqduliogssfqdfalhglmtbrj"},string{"gvfrtkexyjzigcdydnqfpgrxeg"},string{"xgwrgupmdxoepxistovdeqfdcv"},string{"oxggnlexqqmkktpjbzkbfwtydt"},string{"pyopssuxecxbfqgdwjgaglgtmv"},string{"svqwsfwoczrhmiztjgqfqcjyve"},string{"bartebhenxylaavcjnwobeycdy"}};
    cout << "Solution #5" << endl;
    print_list(s.findSubstring(long_string, words5));
}
