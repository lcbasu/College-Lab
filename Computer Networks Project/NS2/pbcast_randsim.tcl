# Copyright (c) 1997 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. All advertising materials mentioning features or use of this software
#    must display the following acknowledgement:
#      This product includes software developed by the Computer Systems
#      Engineering Group at Lawrence Berkeley Laboratory.
# 4. Neither the name of the University nor of the Laboratory may be used
#    to endorse or promote products derived from this software without
#    specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#


# Script to Study probabilistic broadcast in a random network 
 

# ======================================================================
# Define options
# ======================================================================
set val(chan)           Channel/WirelessChannel    ;# channel type
set val(prop)           Propagation/TwoRayGround   ;# radio-propagation model
set val(netif)          Phy/WirelessPhy            ;# network interface type
set val(mac)            Mac/802_11                 ;# MAC type
set val(ifq)            Queue/DropTail/PriQueue    ;# interface queue type
set val(ll)             LL                         ;# link layer type
set val(ant)            Antenna/OmniAntenna        ;# antenna model
set val(ifqlen)         50                         ;# max packet in ifq
set val(nn)             400                        ;# default number of mobilenodes
set val(rp)             AODV                       ;# routing protocol
set val(sc)		"./scenario"		   ;# scenario file
set val(x)		2500.0			   ;
set val(y)		2500.0			   ;
set val(simtime)	10.0			   ; #sim time
# ======================================================================
# Main Program
# ======================================================================

source "./p_bcast.tcl"

if { $argc != 4 } {
        puts "Wrong no. of cmdline args."
	puts "Usage: ns pbcast_randsim.tcl -prob <probability> -scenfile <scenario-file>"
        exit 0
}


proc getopt {argc argv} {
        global val
        lappend optlist prob scenfile 
 
        for {set i 0} {$i < $argc} {incr i} {
                set arg [lindex $argv $i]
                if {[string range $arg 0 0] != "-"} continue
                set name [string range $arg 1 end]
                set val($name) [lindex $argv [expr $i+1]]
        }

         
}


 

getopt $argc $argv


#
# Initialize Global Variables
#
set ns_		[new Simulator]
set tracefd     [open pbsim.tr w]
$ns_ trace-all $tracefd

set namtrace [open pbsim.nam w]           ;# for nam tracing
$ns_ namtrace-all-wireless $namtrace $val(x) $val(y)
$ns_ use-newtrace

# set up topography object
set topo       [new Topography]

$topo load_flatgrid $val(x) $val(y)

#
# Create God
#

set god_ [ create-god $val(nn) ]


# Read in scenario file

source $val(scenfile)



$val(mac) set bandwidth_ 22.0e6 


#
#  Create the specified number of mobilenodes [$val(nn)] and "attach" them
#  to the channel. 

# configure node


        $ns_ node-config -adhocRouting $val(rp) \
			 -llType $val(ll) \
			 -macType $val(mac) \
			 -ifqType $val(ifq) \
			 -ifqLen $val(ifqlen) \
			 -antType $val(ant) \
			 -propType $val(prop) \
			 -phyType $val(netif) \
			 -channelType $val(chan) \
			 -topoInstance $topo \
			 -agentTrace ON \
			 -routerTrace OFF \
			 -macTrace OFF \
			 -movementTrace OFF



	for {set i 0} {$i < $val(nn) } {incr i} {
		set node_($i) [$ns_ node]	
		$node_($i) random-motion 0		;# disable random motion
	}






# Define node initial position in nam

for {set i 0} {$i < $val(nn)} {incr i} {

    # 20 defines the node size in nam, must adjust it according to your scenario
    # The function must be called after mobility model is defined
    
    		$ns_ initial_node_pos $node_($i) 20
		set pbcast_($i) [new Agent/MessagePassing/MyPBCast]
		$ns_ attach-agent $node_($i) $pbcast_($i)
		$node_($i) attach $pbcast_($i) 90
		$pbcast_($i) set agent_port_ 90
		$pbcast_($i) setprob $val(prob)
				
}

	
#
# Tell nodes when the simulation ends
#


$ns_ at 0.0 "$pbcast_(210) send"
for {set i 0} {$i < $val(nn) } {incr i} {
     $ns_ at $val(simtime) "$node_($i) reset";
}
$ns_ at $val(simtime) "stop"
$ns_ at $val(simtime).01 "puts \"NS EXITING...\" ; $ns_ halt"
proc stop {} {
    global ns_ tracefd
    $ns_ flush-trace
    close $tracefd
}

puts "Starting Simulation..."
$ns_ run

