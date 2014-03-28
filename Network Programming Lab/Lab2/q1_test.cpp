/* Protocol 6 (Selective repeat) accepts frames out of order but passes packets to the
network layer in order. Associated with each outstanding frame is a timer. When the timer
expires, only that frame is retransmitted, not all the outstanding frames, as in protocol 5. */
#define MAX SEQ 7 /* should be 2ˆn − 1 */
#define NR BUFS ((MAX SEQ + 1)/2)
typedef enum {frame arrival, cksum err, timeout, network layer ready, ack timeout} event type;
#include "protocol.h"
boolean no nak = true; /* no nak has been sent yet */
seq nr oldest frame = MAX SEQ + 1; /* initial value is only for the simulator */
static boolean between(seq nr a, seq nr b, seq nr c)
{
/* Same as between in protocol 5, but shorter and more obscure. */
return ((a <= b) && (b < c)) || ((c < a) && (a <= b)) || ((b < c) && (c < a));
}
static void send frame(frame kind fk, seq nr frame nr, seq nr frame expected, packet buffer[ ])
{
/* Construct and send a data, ack, or nak frame. */
frame s; /* scratch variable */
s.kind = fk; /* kind == data, ack, or nak */
if (fk == data) s.info = buffer[frame nr % NR BUFS];
s.seq = frame nr; /* only meaningful for data frames */
s.ack = (frame expected + MAX SEQ) % (MAX SEQ + 1);
if (fk == nak) no nak = false; /* one nak per frame, please */
to physical layer(&s); /* transmit the frame */
if (fk == data) start timer(frame nr % NR BUFS);
stop ack timer(); /* no need for separate ack frame */
}
void protocol6(void)
{
seq nr ack expected; /* lower edge of sender’s window */
seq nr next frame to send; /* upper edge of sender’s window + 1 */
seq nr frame expected; /* lower edge of receiver’s window */
seq nr too far; /* upper edge of receiver’s window + 1 */
int i; /* index into buffer pool */
frame r; /* scratch variable */
packet out buf[NR BUFS]; /* buffers for the outbound stream */
packet in buf[NR BUFS]; /* buffers for the inbound stream */
boolean arrived[NR BUFS]; /* inbound bit map */
seq nr nbuffered; /* how many output buffers currently used */
event type event;
enable network layer(); /* initialize */
ack expected = 0; /* next ack expected on the inbound stream */
next frame to send = 0; /* number of next outgoing frame */
frame expected = 0;
too far = NR BUFS;
nbuffered = 0; /* initially no packets are buffered */
for (i = 0; i < NR BUFS; i++) arrived[i] = false;
while (true) {
wait for event(&event); /* five possibilities: see event type above */
switch(event) {
case network layer ready: /* accept, save, and transmit a new frame */
nbuffered = nbuffered + 1; /* expand the window */
from network layer(&out buf[next frame to send % NR BUFS]); /* fetch new packet */
send frame(data, next frame to send, frame expected, out buf);/* transmit the frame */
inc(next frame to send); /* advance upper window edge */
break;
case frame arrival: /* a data or control frame has arrived */
from physical layer(&r); /* fetch incoming frame from physical layer */
if (r.kind == data) {
/* An undamaged frame has arrived. */
if ((r.seq != frame expected) && no nak)
send frame(nak, 0, frame expected, out buf); else start ack timer();
if (between(frame expected,r.seq,too far) && (arrived[r.seq%NR BUFS]==false)) {
/* Frames may be accepted in any order. */
arrived[r.seq % NR BUFS] = true; /* mark buffer as full */
in buf[r.seq % NR BUFS] = r.info; /* insert data into buffer */
while (arrived[frame expected % NR BUFS]) {
/* Pass frames and advance window. */
to network layer(&in buf[frame expected % NR BUFS]);
no nak = true;
arrived[frame expected % NR BUFS] = false;
inc(frame expected); /* advance lower edge of receiver’s window */
inc(too far); /* advance upper edge of receiver’s window */
start ack timer(); /* to see if a separate ack is needed */
}
}
}
if((r.kind==nak) && between(ack expected,(r.ack+1)%(MAX SEQ+1),next frame to send))
send frame(data, (r.ack+1) % (MAX SEQ + 1), frame expected, out buf);
while (between(ack expected, r.ack, next frame to send)) {
nbuffered = nbuffered − 1; /* handle piggybacked ack */
stop timer(ack expected % NR BUFS); /* frame arrived intact */
inc(ack expected); /* advance lower edge of sender’s window */
}
break;
case cksum err:
if (no nak) send frame(nak, 0, frame expected, out buf); /* damaged frame */
break;
case timeout:
send frame(data, oldest frame, frame expected, out buf); /* we timed out */
break;
case ack timeout:
send frame(ack,0,frame expected, out buf); /* ack timer expired; send ack */
}
if (nbuffered < NR BUFS) enable network layer(); else disable network layer();
}
}

int main()
{
	return 0;
}