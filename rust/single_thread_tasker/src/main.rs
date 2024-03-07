use chrono::Local;
use std::time;

#[tokio::main]
async fn main() {
    let start_time = chrono::Local::now();

    let task_handle = tokio::spawn(async move {
        println!("Started task at: {:?}", start_time.format("%Y-%m-%dT%H:%M:%S").to_string());
        std::thread::sleep(time::Duration::from_secs(4));
        Local::now()
    });
    
    let _ = task_handle.await.map(|result| {
        println!("Task handle 'and then' executing...");
        println!("Result of task is: {:?}", result.format("%Y-%m-%dT%H:%M:%S").to_string());
        let time_since = result.time().signed_duration_since(start_time.time());
        println!("Time to execute task was: {:?}", time_since.to_string());
        result
    });
}
