#Probabilistic Broadcast Agent
#V.B., 2005

Class Agent/MessagePassing/MyPBCast -superclass { Agent/MessagePassing }



Agent/MessagePassing/MyPBCast instproc init {} {
	$self instvar prob_ 
	$self instvar seqno_ 
	$self instvar flag_
	$self next
	set seqno_ 0
	set flag_ 0
        $self instvar agent_addr_
	set prob_ 1 
	$self set_pkttype 13
	$self set packetSize_ 256 
}


Agent/MessagePassing/MyPBCast instproc setprob {prob} {
	$self instvar prob_ 
        set prob_ $prob
}
	
Agent/MessagePassing/MyPBCast instproc setseed {seed} {
	$self instvar seed_ 
        set seed_ $seed
        expr srand($seed_)
}

Agent/MessagePassing/MyPBCast instproc send {} {
        $self instvar seqno_ 
	$self instvar agent_addr_
	set msg "pbcast:$agent_addr_:$agent_addr_:$seqno_:"
        set flag_ 1	
	$self sendto 256 $msg -1 90	
}

Agent/MessagePassing/MyPBCast instproc recv { flg port len p } {
      # receiver function
      $self instvar agent_addr_
      $self instvar flag_
      $self instvar prob_ 
      set L [split $p :]
      set src_ [lindex $L 2]
      set seqno_ [lindex $L 3]
      if {$flag_ == 1} {  return }
      set flag_ 1	
      #here toss a coin and make probabilistic decision
      set coin [expr rand()]
	#puts $coin
	#puts $prob_
      if {$coin > $prob_} { return }
      set msg "pbcast:$agent_addr_:$src_:$seqno_:"
      $self sendto 256 $msg -1 90
	
}
