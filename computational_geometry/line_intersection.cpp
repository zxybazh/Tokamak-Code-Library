inline bool line_inter_judge(Vec p1, Vec p2, Vec q1, Vec q2) {
	if (dcmp(max(p1.x, p2.x), min(q1.x, q2.x)) < 0) return false ;
	if (dcmp(max(q1.x, q2.x), min(p1.x, p2.x)) < 0) return false ;
	if (dcmp(max(p1.y, p2.y), min(q1.y, q2.y)) < 0) return false ;
	if (dcmp(max(q1.y, q2.y), min(p1.y, p2.y)) < 0) return false ;
	return  dcmp((p2 - p1).det(q1 - p1)) * dcmp( (p2 - p1).det(q2 - p1) ) <= 0 && 
		dcmp((q2 - q1).det(p1 - q1)) * dcmp( (q2 - q1).det(p2 - q1) ) <= 0;
}
inline Vec line_inter(const vec &a1, const vec &a2, const vec &b1, const vec &b2) {
    double s1 = (a2 - a1).det(b1 - a1);
    double s2 = (a2 - a1).det(b2 - a1);
    return (b1 * s2 - b2 * s1) / (s2 - s1);
}
