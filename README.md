# Riak-destination
Steps:
* `git clone https://github.com/hTrap/riak_dest.git`
* `cd riak_dest`
* `protoc-c --c_out=. riak.proto`
* `gcc cliento.c  riak.pb-c.c -o client -lprotobuf-c`
* `./client localhost 8087`
