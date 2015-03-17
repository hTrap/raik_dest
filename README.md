# Riak-destination
Steps:
* `git clone https://github.com/hTrap/raik_dest.git`
* `cd raik_dest`
* `protoc-c --c_out=. riak.proto`
* `protoc-c --c_out=. amessage.proto`
* `gcc cliento.c amessage.pb-c.c riak.pb-c.c -o client -lprotobuf-c`
* `./client localhost 8087 7 9`
