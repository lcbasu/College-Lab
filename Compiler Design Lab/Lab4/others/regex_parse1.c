/** a program to convert a simple regex expression
 * into a traversable tree
 *
 * the regex operators are none ( concatenate), | (unify or alternate), and * ( kleene star)
 * the order of precedence of is kleene star, concatenate and alternate.
 *  e.g.  ab*c | e*d    is  (a(b*)c) | ((e*)d)
 *
 *  this program is a variation of the infix expression to postfix expression program,
 *  which is a program that converts bracketed normal arithmetic expressions into 
 *  reverse polish notation, which can be pushed onto a stack in sequence to get a result.
 *  
 *  what this program illustrates is the manual conversion of a simple top-down context-free grammar
 *  for regular expressions into a recursive program .
 *  An important point about top-down parsers , is that the right hand side of the grammar
 *  must not have a possibility which calls the left hand side first. 
 *  e.g.  expr = term | expr "|" term    , would lead to expr() calling expr() first, and endlessly recursing.
 *
 *  the program uses a stack to store nodes of a parse tree. Leaf nodes are the literals , the actual
 *  characters used for matching. Interior nodes are operation nodes , e.g. star, concat, or unify (alternate).
 *  
 *  A regular expression matcher is an essential part of a program like "lex" which is a lexer, 
 *  a program to convert a stream of characters in a file into tokens to be later recognized by
 *  yacc , a language parser. The language parser can be produced from a grammar similiar
 *  to the one below.  
 *
 *  The parse tree that is built by this regex parser, is one similiar to
 *  the example tree in the lexical analysis chapter of "Compilers, Principles, Techniques and Tools".
 *  In this chapter, it shows how to convert such a parse tree into a nondeterministic finite automata
 *  (NFA) graphically. Then it shows there is an algorithm which uses "finding the e-closure set"
 *  to construct sets of positions, which are then labelled as states in a deterministic finite automata
 *  (DFA). The DFA is useful because for any state and a given single symbol, there is only one
 *  transition from that state (so that the automata is deterministic given a state and a symbol to 
 *  transit on). 
 *  The key first step , is that in constructing the NFA, the automata parts for kleene-star has
 *  e transitions , and the for alternation/unify  , has e transitions. e transitions are transitions
 *  given no symbol. The algorithm for NFA construction is called Thompson's construction.
 *
 *  The chapter then discusses converting a regex parse tree directly into a DFA, 
 *  using an algorithm which depends on having a accepting state symbol '#' near the top of the parse tree,
 *  which is associated with a position in the parse tree. 
 *  It uses properties of nodes in the parse tree called "nullable", "firstpos", "lastpos" and "followpos",
 *  and I still can't work out how they worked out the algoritm, but it depends on having a parse tree.
 *
 *  The "nullable" property is the answer to the question "can this node be null?" :
 *  kleene-star , which is zero or more,  is always nullable,  and leaf nodes, are never nullable. 
 *  Alternate is nullable if either operands are nullable, and concatenation is nullable if both operands
 *  are nullable.
 *
 *  "firstpos" is the possible entry positions for the node : leaf nodes are labelled sequentially, and
 *  given a single firstpos values.  lastpos is the same as firstpos, but for any conditional statements
 *  uses the second node instead of the first node. For leaf nodes, lastpos is the same as firstpos.
 *  "firstpos" for kleene star is the same as the firstpos of the node it operates on.
 *  "firstpos" for alternation, is either the firstpos of the first operand or the firstpos of the second
 *  operand, so is the union of the firstpos's of its 2 operands.
 *  "firstpos" for concatenation, is the firstpos of the first operand if it is not nullable, because
 *  it will always be there, but if it can be nulled, then it is the union of the firstpos of the
 *  two operands , because the second operands firstpos will show through if the first operand is null.
 *
 *  As mentioned before, lastpos basically means concatenation's firstpos set depends on the second operand
 *  being nullable, but the lastpos is the same as firstpos for all other nodes.
 *
 *  Finally , there is "followpos". The "followpos" property is for operators that can associate one or more nodes
 *  to follow another node, so this means the kleene-star operator ( when there is 1 or more), 
 *  and the concatenation operator.  For kleene-star, for each position in the lastpos of the kleene-star,
 *  the followpos sets of those positions contain the firstpos positions of the kleene-star node. 
 *  ( all firstpos of kleene-star node, are in followpos of each position in lastpos of kleene-star node).
 *  For the concat operator, all the firstpos of the second operand's child node, which follows the first operand,
 *  is in the followpos set of the positions of the lastpos set in the first operand child node.
 *  ( Note , it isn't the firstpos positions of the concat operator and its lastpos position, but the rule
 *  is operating on the child nodes associated by the concat operator node ).
 *
 *  From , this a table of positions, and followpos set for a given position can be constructed.
*  Initially, the positions had been labelling of the leaf nodes of the parse tree which contain
*  the   symbols (i.e. characters)  that cause a transition between states. There is also a position associated
*  with a termination symbol '#' , and any state that is constructed containing the termination symbol
*  is regarded as an accepting state.
*
*  To construct the DFA once nullable, firstpos, lastpos for each node is calculated, and
*  the follow pos table is found,  the algorithm begins with the top of the parse tree
*  and uses the firstpos set of the root node as the starting input.
*  for each type of symbol, check to see if it is associated with a position in the current set.
*  If it is, add the followpos for that position from the followpos table to the next set of positions
*  to be examined. The next set of positions constructed is then a state , which is a state
*  that transits from the current set of positions, also a state, given the symbol being checked.
*  If the set is unique, it is added to the list of sets which will become the current set to be examined.
*  This will construct a table of state1 -> symbol -> state2 , which is the DFA.
*  The DFA can then be used for regex matching by feeding a string input into the DFA starting
*  at the first state, and if it ends up on the accepting state, then the string is a match.
*
 *
 *  
 *  
 */
#include "parsenode.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* the grammar to parse top down is 
 *
 * start =  expr 
 * expr  =  term | term "|" expr
 * term  =  factor | factor term
 * factor =  subfactor | subfactor "*"
 * subfactor = literal | (expr) 
 * literal =  letters | digits
 * digits = '0'|'1'..|'9'
 * letters = lowercase | uppercase
 * lowercase = 'a'| 'b'| 'c'| 'd'..|'z'
 * uppercase = 'A' | 'B' | 'C' .. | 'Z'
 *
 */


int expr() ;
int term();
int factor();
int subfactor();
int literal();
int letters();
int digits();
int lowercase();
int uppercase();

/* node actions
	| = unify();
	ab  = concat();
	* = star();
*/

int unify();
int cat();
int star();
int parenthesis();

void error (const char* message);
void showstack();
void shownode(node_p, int);

int lookahead();
int putback();
int mark();
int unmark();


int nextchar;

#define MAXLOOKAHEAD 1000
int buffer[MAXLOOKAHEAD];
int curr = 0;
int catchup = 0;
int marking = 0;

int lookahead() {
	nextchar = getchar();
}

int putback() {
	ungetc(nextchar, stdin);
}

/* stack for parsing */
#define MAXSTACK 1000

node_p nodestack[MAXSTACK];
int node_pos = 0;

node_p pop() {
	if ( node_pos > 0 ) {
		return nodestack[--node_pos];
	}
	return 0;
}

int push( node_p pnode) {
	if (node_pos < MAXSTACK ) {
		nodestack[node_pos++] = pnode;	
		return 1;
	}
	return 0;
}

node_p makenode( node_p left, node_p right, int value) {
	node_p pnode = malloc( sizeof ( node_t ) );
	pnode->left = left;
	pnode->right = right;
	pnode->value = value;

	return pnode;
}

node_p parentnode ( node_p left, node_p right, int value) {
	return makenode( left, right, value);
}

node_p leafnode ( int value) {
	return makenode ( NULL, NULL, value);
}


void showstack() {
	int i;

	for (i = 0; i < node_pos; ++i) {
		printf("\n\nStack pos %d", i);
		shownode(nodestack[i], 0);
	}
	printf("\n\n");

}
void shownode(node_p pnode, int depth) {
	int i;
	if (pnode) {
		
		shownode(pnode->left, depth+1);

		for (i = 0; i < depth; ++i ) 
			printf("  ");

		printf("value is %d %c\n", pnode->value, pnode->value);	
		shownode(pnode->right, depth+1);
	}
	
}


int start() {
	if ( ! expr() ) 
		error("failed to parse");

}

int expr() {
	term(); lookahead();
	if (nextchar == '|') {
		expr();
		unify();
	}
	else {
		putback();
	}
	return 1;
}

int term() {
	int result = factor();
	if (result && term() ) {
		result = concat();
	}
	return result;
}
	
int factor() {
	int result = subfactor(); 
	lookahead();
	if ( nextchar == '*' ) {
		result =  star();
	} else {
		putback();
	}
	return result;

}

int subfactor() {
	int result;
	lookahead();
	if ( nextchar == '(') {
		expr();
		lookahead();
		if ( nextchar == ')') {
			result =  parenthesis();			
		} else {
			error( "unbalance parenthesis");
			showstack();
			exit(1);
		}
	} else {
		putback();
		result =  literal();
	}

	return result;
}

int literal() {
	if (! letter() &&  !digit() && !dot() )  {
		return 0;
	}
	return 1;
	
}

int letter() {
	if ( lowercase())
		return 1;
	else
		return uppercase() ;
}

int digit() {
	lookahead();
	if ( isdigit(nextchar) ) {
		push( leafnode( nextchar ) );		
		return 1;
	}
	putback();
	return 0;
}

int lowercase() {
	lookahead();
	if ( islower( nextchar) ) {
		push( leafnode ( nextchar ) );
		return 1;
	}
	putback();
	return 0;
}


int uppercase() {
	lookahead();
	if ( isupper(nextchar) ) {
		push ( leafnode( nextchar ) );
		return 1;
	}
	putback();
	return 0;
}

int dot() {
	int result = 0;
	lookahead();
	if ( nextchar == '.') {
		push ( leafnode( DOT) );
		result = 1;
	} else {
		putback();
	}
	return result;
}

int star() {
	return push ( parentnode( pop(), NULL , STAR ) );
}

int unify() {
	return push ( parentnode( pop(), pop(), UNIFY) );
}

int concat() {
	node_p left, right;
	right = pop();
	left = pop();
	return push ( parentnode( left, right, CONCAT ) );
}

int parenthesis() {
	return 1;
}
	
#ifndef NFA_MAIN	
int main(int argc, char* argv[]) {
	node_p root;
	start();
	root = pop();
	shownode(root , 0);
	
	return 0;
}
#endif
