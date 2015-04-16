# Riak-destination
Steps:
* `git clone https://github.com/hTrap/riak_dest.git`
* `cd riak_dest`
* `protoc-c --c_out=. riak.proto`
* `protoc-c --c_out=. riak_kv.proto`
* `gcc cliento.c  riak_kv.pb-c.c riak.pb-c.c -o client -lprotobuf-c`
* `./client localhost 8087`
