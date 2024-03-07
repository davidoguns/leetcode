use bytes::Bytes;
use std::collections::HashMap;
use std::sync::{Arc, Mutex};
use mini_redis::{Connection, Frame};
use tokio::net::{TcpListener, TcpStream};

type Db = Arc<Mutex<HashMap<String, Bytes>>>;

#[tokio::main]
async fn main() {
    const PORT: i16 = 6397;
    let listener = TcpListener::bind(format!("127.0.0.1:{}", PORT)).await.unwrap();

    println!("Listening to port {:?}", PORT);

    let db = Arc::new(Mutex::new(HashMap::<String, Bytes>::new()));

    loop {
        let (socket, addr) = listener.accept().await.unwrap();
        let db = db.clone();
        println!("Accepted on port: {:?}", addr.port());
        tokio::spawn(async move {
            process_mutex(socket, db).await;
        });
    }
}

async fn process_mutex(socket: TcpStream, db: Db) {
    use mini_redis::Command::{self, Get, Set};
    let mut connection = Connection::new(socket);

    while let Some(frame) = connection.read_frame().await.unwrap() {
        let response = match Command::from_frame(frame).unwrap() {
            Set(cmd) => {
                let mut db = db.lock().unwrap();
                db.insert(cmd.key().to_string(), cmd.value().clone());
                Frame::Simple("OK".to_string())
            }
            Get(cmd) => {
                let db = db.lock().unwrap();
                if let Some(value) = db.get(cmd.key()) {
                    Frame::Bulk(value.clone())
                } else {
                    Frame::Null
                }
            }
            cmd => panic!("unimplemented {:?}", cmd),
        };
        connection.write_frame(&response).await.unwrap();
    }
}
