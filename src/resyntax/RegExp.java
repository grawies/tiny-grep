package automata.resyntax;

import java.util.ArrayList;

import automata.GraphPrintable;
import util.Util;

public abstract class RegExp implements GraphPrintable {

	public String toGraph() {
		return toGraph(10);
	}
	public String toGraph(int pngsize) {
		ArrayList<String> nodes = new ArrayList<String>();
		ArrayList<String> edges = new ArrayList<String>();
		generateGraphLines(nodes, edges);
		
		StringBuilder sb = new StringBuilder("digraph epsilon_nfa {\nrankdir=LR; size=\""+pngsize+","+pngsize+"\";\n");
		sb.append("node [shape = circle];\n");
		
		for (String s : nodes) {
			sb.append(s);
		}
		for (String s : edges) {
			sb.append(s);
		}

		sb.append("}\n");
		return sb.toString();
		
	}

	private void generateGraphLines(ArrayList<String> nodes, ArrayList<String> edges) {
		int n = nodes.size();
		String symbol;

		if (this instanceof Literal || this instanceof Dot) {
			
			if (this instanceof Literal) {
				Character c = ((Literal) this).c;
				symbol = Util.charToString(c);
			} else {
				symbol = "dot";
			}
			
			nodes.add(Integer.toString(n) + " [label=\"" + symbol + "\"];\n");
			
		} else if (this instanceof OneOrMore || this instanceof ZeroOrOne || this instanceof Closure) {
			RegExp target;

			if (this instanceof OneOrMore) {
				symbol = "+";
				target = ((OneOrMore) this).r;
			} else if (this instanceof ZeroOrOne) {
				symbol = "?";
				target = ((ZeroOrOne) this).r;
			} else {
				symbol = "*";
				target = ((Closure) this).r;
			}

			// add a node for the operation
			nodes.add(Integer.toString(n) + " [label=\"" + symbol + "\"];\n");
			// add an edge to the target RegExp
			edges.add(Integer.toString(n) + " -> " + Integer.toString(n + 1) + ";\n");
			// add the target RegExp
			target.generateGraphLines(nodes, edges);
			
		} else if (this instanceof Concatenation || this instanceof Union) {
			RegExp target1, target2;
			
			if (this instanceof Concatenation) {
				symbol = "&";
				target1 = ((Concatenation)this).r1;
				target2 = ((Concatenation)this).r2;
			} else{
				symbol = "|";
				target1 = ((Union)this).r1;
				target2 = ((Union)this).r2;
			}
			// add a node for operation
			nodes.add(Integer.toString(n) + " [label=\"" + symbol + "\"];\n");
			// add an edge to the first target RegExp
			edges.add(Integer.toString(n) + " -> " + Integer.toString(n + 1) + ";\n");
			// add the target RegExp
			target1.generateGraphLines(nodes, edges);
			// add an edge to the second target RegExp - where has changed size
			edges.add(Integer.toString(n) + " -> " + Integer.toString(nodes.size()) + ";\n");
			// add the target RegExp
			target2.generateGraphLines(nodes, edges);
		}

	}
}
