# HOTspot 

## what it is
This porject is meant to be a cli tool port scanner that is the basic reconnisance in search of vulnerabilties or risky open ports that could be taken advantage of. 

## what it does
as of march 14th, all it does is scan the 4040 TCP port of the given ipv4 address if no specific port is given into the arguement. will output the ports open and then number the ammount of closed ports.

## what i hope to improve
currently, i am only scanning through tcp ports and would hope to someday get through with udp ports as well. i have also noticed how nmap has a structure whn runnign the scanner (PORT  STATE  SERVICE  VERSION) and hope to include those things into mine as i sometimes have to search up what some of them even mean or are