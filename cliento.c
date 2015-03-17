#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "amessage.pb-c.h"
#include "riak.pb-c.h"

       

        int
        main(int argc, char *argv[])
       {
           struct addrinfo hints;
           struct addrinfo *result, *rp;
           int sfd, s, j,sb;
           
                      

           if (argc < 3) {
               fprintf(stderr, "Usage: %s host port msg...\n", argv[0]);
               exit(EXIT_FAILURE);
           }

           /* Obtain address(es) matching host/port */

           memset(&hints, 0, sizeof(struct addrinfo));
           hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
           hints.ai_socktype = SOCK_STREAM; 
           hints.ai_flags = 0;
           hints.ai_protocol = 0;          /* Any protocol */

           s = getaddrinfo(argv[1], argv[2], &hints, &result);
           if (s != 0) {
               fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
               exit(EXIT_FAILURE);
           }

           /* getaddrinfo() returns a list of address structures.
              Try each address until we successfully connect(2).
              If socket(2) (or connect(2)) fails, we (close the socket
              and) try the next address. */

           for (rp = result; rp != NULL; rp = rp->ai_next) {
               sfd = socket(rp->ai_family, rp->ai_socktype,
                            rp->ai_protocol);
               if (sfd == -1)
                   continue;

               if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
                   break;                  /* Success */

               close(sfd);
           }

           if (rp == NULL) {               /* No address succeeded */
               fprintf(stderr, "Could not connect\n");
               exit(EXIT_FAILURE);
           }

           freeaddrinfo(result);        


           AMessage msg = AMESSAGE__INIT; // AMessage
            void *buf;                     // Buffer to store serialized data
            unsigned len;                  // Length of serialized data
        
            if (argc != 4 && argc != 5)
              {   // Allow one or two integers
                fprintf(stderr,"usage: amessage a [b]\n");
                return 1;
               }
        
            msg.a = atoi(argv[3]);
            if (argc == 5) { msg.has_b = 1; msg.b = atoi(argv[4]); }
            len = amessage__get_packed_size(&msg);
        
            buf = malloc(len);
            amessage__pack(&msg,buf);   

            if (sb = send(sfd,buf,len,0) == -1)
            {
              fprintf(stderr,"error sending");
              exit(EXIT_FAILURE);

            }
            printf("Number of bytes sent :%d", sb);
            close(sfd);

           

           exit(EXIT_SUCCESS);
       }


