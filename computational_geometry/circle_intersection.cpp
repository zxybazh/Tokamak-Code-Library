inline double is_cir_inter(Vec &o1, double r1, double x) {
	return dcmp(o1.x - r1, x) <= 0 && dcmp(x, o1.x + r1) <= 0;
}
inline pair<Vec, Vec> cir_inter(Vec &o1, double r1, Vec &o2, double r2) {
	double d = (o1 - o2).norm();
	double cost = (r1*r1 + d*d - r2*r2)/(2.*r1*d), sint = sqrt(max(0., 1. - cost*cost));
	Vec o = o1 + (o2 - o1).unit() * (r1*cost), u = (o1 - o2).unit().rot90() * (r1*sint);
	return make_pair(o + u, o - u);
}
