struct C1{
	double map[6][24*24];
	double kernel[6][5*5];
	double bias[6];
};

struct S2{
	double map[6][12*12];
//	double kernel[6][2*2];
};

struct C3{
	double map[12][8*8];
	double kernel[12*6][5*5];
	double bias[12];
};

struct S4{
	double map[12][4*4];
//	double kernel[12][2*2];
};

struct Output{
	double map[10];
	double w[10][12*4*4];
	double bias[10];
};

