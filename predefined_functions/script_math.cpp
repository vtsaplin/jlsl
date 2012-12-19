#include "../script_parser.h"

// return absolute value
script_container math_abs (vector<script_container>& args) {
	script_container c;
	c.set_single (fabs (args [0].to_single ()));
	return c;
}
script_predefined_function math_abs_def ("abs", math_abs, 1);

// calculate arccosine 
script_container math_acos (vector<script_container>& args) {
	script_container c;
	c.set_single (acos (args [0].to_single ()));
	return c;
}
script_predefined_function math_acos_def ("acos", math_acos, 1);

// calculate arcsine 
script_container math_asin (vector<script_container>& args) {
	script_container c;
	c.set_single (asin (args [0].to_single ()));
	return c;
}
script_predefined_function math_asin_def ("asin", math_asin, 1);

// calculate arctangent 
script_container math_atan (vector<script_container>& args) {
	script_container c;
	c.set_single (atan (args [0].to_single ()));
	return c;
}
script_predefined_function math_atan_def ("atan", math_atan, 1);

// calculate arctangent, 2 parameters 
script_container math_atan2 (vector<script_container>& args) {
	script_container c;
	c.set_single (atan2 (args [0].to_single (), args [1].to_single ()));
	return c;
}
script_predefined_function math_atan2_def ("atan2", math_atan2, 2);

// return the smallest integer that is greater or equal to x 
script_container math_ceil (vector<script_container>& args) {
	script_container c;
	c.set_single (ceil (args [0].to_single ()));
	return c;
}
script_predefined_function math_ceil_def ("ceil", math_ceil, 1);

// calculate cosine 
script_container math_cos (vector<script_container>& args) {
	script_container c;
	c.set_single (cos (args [0].to_single ()));
	return c;
}
script_predefined_function math_cos_def ("cos", math_cos, 1);

// calculate hyperbolic cosine
script_container math_cosh (vector<script_container>& args) {
	script_container c;
	c.set_single (cosh (args [0].to_single ()));
	return c;
}
script_predefined_function math_cosh_def ("cosh", math_cosh, 1);

// calculate exponential 
script_container math_exp (vector<script_container>& args) {
	script_container c;
	c.set_single (exp (args [0].to_single ()));
	return c;
}
script_predefined_function math_exp_def ("exp", math_exp, 1);

// round down value 
script_container math_floor (vector<script_container>& args) {
	script_container c;
	c.set_single (floor (args [0].to_single ()));
	return c;
}
script_predefined_function math_floor_def ("floor", math_floor, 1);

// calculate natural logarithm 
script_container math_log (vector<script_container>& args) {
	script_container c;
	c.set_single (log (args [0].to_single ()));
	return c;
}
script_predefined_function math_log_def ("log", math_log, 1);

// calculate logarithm base 10 
script_container math_log10 (vector<script_container>& args) {
	script_container c;
	c.set_single (log10 (args [0].to_single ()));
	return c;
}
script_predefined_function math_log10_def ("log10", math_log10, 1);

// calculate numeric power
script_container math_pow (vector<script_container>& args) {
	script_container c;
	c.set_single (pow (args [0].to_single (), args [1].to_single ()));
	return c;
}
script_predefined_function math_pow_def ("pow", math_pow, 2);

// calculate sine 
script_container math_sin (vector<script_container>& args) {
	script_container c;
	c.set_single (sin (args [0].to_single ()));
	return c;
}
script_predefined_function math_sin_def ("sin", math_sin, 1);

// calculate hyperbolic sine 
script_container math_sinh (vector<script_container>& args) {
	script_container c;
	c.set_single (sinh (args [0].to_single ()));
	return c;
}
script_predefined_function math_sinh_def ("sinh", math_sinh, 1);

// calculate square root 
script_container math_sqrt (vector<script_container>& args) {
	script_container c;
	c.set_single (sqrt (args [0].to_single ()));
	return c;
}
script_predefined_function math_sqrt_def ("sqrt", math_sqrt, 1);

// calculate tangent 
script_container math_tan (vector<script_container>& args) {
	script_container c;
	c.set_single (tan (args [0].to_single ()));
	return c;
}
script_predefined_function math_tan_def ("tan", math_tan, 1);

// calculate hyperbolic tangent 
script_container math_tanh (vector<script_container>& args) {
	script_container c;
	c.set_single (tanh (args [0].to_single ()));
	return c;
}
script_predefined_function math_tanh_def ("tanh", math_tanh, 1);
