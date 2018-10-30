
#create simulator object
set ns [new Simulator]

#set colors
$ns color 1 Red
$ns color 2 Blue

#OPEN NAM TRANCE FIL-all $E
set nf [open b2_vnk.nam w]
$ns namtrace-all $nf

#finish procu=edure
proc finish {} {
global ns nf
$ns flush-trace
#close the trace file
close $nf
#execute nam file
exec nam b2_vnk.nam &
exit 0
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

$ns duplex-link $n0 $n2 2Mb 10ms DropTail
$ns duplex-link $n1 $n2 2Mb 10ms DropTail
$ns duplex-link $n2 $n3 1.4Mb 10ms DropTail
$ns duplex-link $n0 $n1 2Mb 10ms DropTail

#Set QueSize limit
$ns queue-limit $n2 $n3 10

#give positioning to the links
$ns duplex-link-op $n0 $n2 orient right-down
$ns duplex-link-op $n1 $n2 orient right-up
$ns duplex-link-op $n2 $n3 orient right

#monitoring the queue
$ns duplex-link-op $n2 $n3 queuePos 0.5

#set tcp connection
set tcp [new Agent/TCP]
$tcp set class_ 2
$ns attach-agent $n0 $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n3 $sink
$ns connect $tcp $sink
$tcp set fid_ 1

#set ftp over tcp
set ftp [new Application/FTP]
$ftp attach-agent $tcp 
$ftp set type_ FTP

#set udp
set udp [new Agent/UDP]
$ns attach-agent $n1 $udp
set null [new Agent/Null]
$ns attach-agent $n3 $null
$ns connect $udp $null
$udp set fid_ 2

#cbr setup
set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set type_ CBR
$cbr set packet_size_ 1000
$cbr set rate_ 1Mb
$cbr set random_ false

$ns at 0.1 "$cbr start"
$ns at 0.2 "$ftp start"
$ns at 4.0 "$ftp stop"
$ns at 4.5 "$cbr stop"
$ns at 5.0 "finish"

$ns run
