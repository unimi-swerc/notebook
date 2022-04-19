friend T getFunc(sn a, int b) { return a?a->func[b]:T{1,0}; }
void prop() { // lazy prop
	if (!flip) return;
	swap(c[0],c[1]); swap(func[0],func[1]);
	flip = 0;
	F0R(i,2) if (c[i]) c[i]->flip ^= 1;
}
void calc() { // recalc vals
	F0R(i,2) if (c[i]) c[i]->prop();
	sz = 1+getSz(c[0])+getSz(c[1]);
	sub = 1+getSub(c[0])+getSub(c[1])+vsub;
	func[0] = getFunc(c[0],0)+val+getFunc(c[1],0);
	func[1] = getFunc(c[1],1)+val+getFunc(c[0],1);
}
