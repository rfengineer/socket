NOTE: I've been reading and getting lost. Many "references" seem to be vague.  Others contradict. 
MAN(7) UNIX
MAN(2) SOCKET
Linux Programming By Example (WALL)
Linux Socket Programming by Example (GAY)
C By Example (Perry)
freebsd.org/doc/en/books/developers-handbook/sockets-essential-functions.html
several other sources. 

Certainly I know and understand enough code I could easily cut/past someone else's code 
and cobble something that would work, but that would be close akin to putting a plastic gear 
inside a metal transmission. It may work for a while, but it could fail - and unless I know 
the substance of the materials I'm injecting into the system, I won't know if, how, how soon, 
or why it failed, much less understand how to fix it.  

I indeed need to know more about the socket() command, as well as other commands involved in the 
creation and use of a TCP/IP socket in *Nix.

I've watched several videos on the topic.  Everybody is quick to type out the code as if they've either
memorized it or are reading it from a script. Nobody seems to EXPLAIN it, what it does or why it works - 
why this or that is needed (or isn't) in a given application. Certainly each command has a purpose or it 
wouldn't be included in the program.  Just typing it out doesn't prove that you know it.  It proves that 
you can read a character at a time and parrot it out to a terminal. This stuff I have to know and understand 
as well as I do the standard "Hello World" program.  (Why does this author use printf, that one use puts, and 
the other use putc, and what is the difference.)  The same is true with sa_family and AF_UNSPEC. All of this 
is standard terminology and must have an etymology. 

Inclusions:
ALL authors seem to include:
#include <sys/socket.h> - required for ALL sockets 
#include <sys/types.h> - ???? // the SOCKET(2) man says that it is necessary. "some historical (BSD) implementations required this header file, and portable applications are probably wise to include it."

and of course the ubiquitous:
#include <stdio.h> - input/output functions
#include <stdlib.h> - system commands
#include <unistd.h> - POSIX standard

Some also include:
#include<arpa/inet.h>  - ???
#include<netinet/in.h>  -???
#include<sys/un.h> - ???
reasons are yet unclear.

Common Elements:
The SOCKET
int socket(int domain, int type, int protocol);
requirements:
  #include <sys/socket.h>
  #include <sys/types.h>
  
  int domain appears to be protocol (and protocol is the domain?)
  int domain is PF_INET (Protocol Family - Internet)
      or it can be PF_UNIX for local use
  
  int type appears to be type of connection
      SOCK_DGAM ( datagram or UDP )
      SOCK_STREAM ( TCP stream )
      
  int protocol - everybody uses "0"
  socket(PF_UNIX,SOCK_STREAM,0) - Kurt Wall
  socket(PF_INET, SOCK_STREAM,0); - freebsd developers handbook
  socket(AF_UNIX,type,0); - Unix(7) man page

    This seems to be a point of question:
    According to the socket(2) man page, as well as the freebsd.org developers handbook, 
    int socket(int domain, int type, int protocol) is the way socket is used. 
    the last variable - int protocol - is described in the socket(2) man page as:
    "specifies a PARTICULAR protocol to be used with the socket" but it doesn't tell you 
    what those protocols are (with the exception of them being an integer). Instead it
    refrences protocols(5). which says to use the IANA standard. It gives reference to the 
    address of the standard (http://www.iana.org/assignments/protocol-numbers)
    I went there and it described the protocol as follows:
      0 	HOPOPT 	IPv6 Hop-by-Hop Option 	Y 	[RFC8200]
      1 	ICMP 	Internet Control Message 		[RFC792]
      2 	IGMP 	Internet Group Management 		[RFC1112]
      3 	GGP 	Gateway-to-Gateway 		[RFC823]
      4 	IPv4 	IPv4 encapsulation 		[RFC2003]
      5 	ST 	Stream 		[RFC1190][RFC1819]
      6 	TCP 	Transmission Control
        ...etc
    By this, I would think that we should use either 4 (IPv4) or 6(TCP) for a TCP/IP protocol over IPv4.
    However, everyone seems to use 0 which is IPV6 hop-by-hop.  SOOO confusing as to why???
    
    

  There is a specific order of tasks that need to be accomplished:
1) Create the socket (with the socket() command)
2) Bind the socket to an address
3) Listen
4) Accept

  Address Families should match Protocol Families
  (PF_INET --> AF_INET and PF_UNIX --> AF_UNIX)
  
