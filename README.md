# HOTspot 

## what it is
This porject is meant to be a cli tool port scanner that is the basic reconnissance in search of vulnerabilties or risky open ports that could be taken advantage of. 

## what it does
it scans all 65535 tcp ports through async connections at a batch of 100 syncs. it can tell you whether the port is open or filtered and skips all the closed ports.

## what i hope to improve
currently, i am only scanning through tcp ports and would hope to someday get through with udp ports as well. I would add fingerprinting and banner grabbing