//----------------DeepPipe2 my implementation of Deep-Learning in Elixir-----------
//   I will port DeepPipe2 code from Elixir to Easy-ISLisp in 2021
/*



  /*
  random_select for matrix data
  */
  static ERL_NIF_TERM
  random_select1(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
	  ErlNifBinary  a_bin,b_bin;
	  ERL_NIF_TERM  c_bin,d_bin,tuple;
	  int r1, c1, r2, c2, i, j, n, r;
	  float *a, *b, *c, *d;
	
	  if (!enif_get_int(env, argv[0], &r1)) return enif_make_int(env,1);
	  if (!enif_get_int(env, argv[1], &c1)) return enif_make_int(env,2);
	  if (!enif_inspect_binary(env, argv[2], &a_bin )) return enif_make_int(env,3);
	  if (!enif_get_int(env, argv[3], &r2)) return enif_make_int(env,4);
	  if (!enif_get_int(env, argv[4], &c2)) return enif_make_int(env,5);
	  if (!enif_inspect_binary(env, argv[5], &b_bin )) return enif_make_int(env,6);
	  if (!enif_get_int(env, argv[6], &n)) return enif_make_int(env,7);
  
	  a = (float *) a_bin.data;
	  b = (float *) b_bin.data;
	  c = (float *) enif_make_new_binary(env, n*c1 * sizeof(float), &c_bin);
	  d = (float *) enif_make_new_binary(env, n*c2 * sizeof(float), &d_bin);
  
  
	  // random-select
	  for(i=0;i<n;i++){
		  r = rand() % r1;
		  for(j=0;j<c1;j++){
			  c[IDX2C(i,j,n)] = a[IDX2C(r,j,r1)];
		  }
		  for(j=0;j<c2;j++){
			  d[IDX2C(i,j,n)] = b[IDX2C(r,j,r2)];
		  }    
	  }
  
	  tuple = enif_make_tuple2(env,c_bin,d_bin);
	  return(tuple);
  }
  
  /*
  random_select for 4D-tensor data
  */
  static ERL_NIF_TERM
  random_select2(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
	  ErlNifBinary  a_bin,b_bin;
	  ERL_NIF_TERM  c_bin,d_bin,tuple;
	  int n1,c1,h1,w1,r2,c2, i, j, k, l, n, r;
	  float *a, *b, *c, *d;
	
	  if (!enif_get_int(env, argv[0], &n1)) return enif_make_int(env,1);
	  if (!enif_get_int(env, argv[1], &c1)) return enif_make_int(env,2);
	  if (!enif_get_int(env, argv[2], &h1)) return enif_make_int(env,3);
	  if (!enif_get_int(env, argv[3], &w1)) return enif_make_int(env,4);
	  if (!enif_inspect_binary(env, argv[4], &a_bin )) return enif_make_int(env,5);
	  if (!enif_get_int(env, argv[5], &r2)) return enif_make_int(env,6);
	  if (!enif_get_int(env, argv[6], &c2)) return enif_make_int(env,7);
	  if (!enif_inspect_binary(env, argv[7], &b_bin )) return enif_make_int(env,8);
	  if (!enif_get_int(env, argv[8], &n)) return enif_make_int(env,9);
  
	  a = (float *) a_bin.data;
	  b = (float *) b_bin.data;
	  c = (float *) enif_make_new_binary(env, n*c1*h1*w1 * sizeof(float), &c_bin);
	  d = (float *) enif_make_new_binary(env, n*r2*c2 * sizeof(float), &d_bin);
  
	  // random-select
	  for(i=0;i<n;i++){
		  r = rand() % n1;
		  for(j=0;j<c1;j++){
			  for(k=0;k<h1;k++){
				  for(l=0;l<w1;l++){
					  c[IDX4C(i,j,k,l,c1,h1,w1)] = a[IDX4C(r,j,k,l,c1,h1,w1)];
				  }
			  }
		  }
		  for(j=0;j<c2;j++){
			  d[IDX2C(i,j,n)] = b[IDX2C(r,j,r2)];
		  }    
	  }
  
	  tuple = enif_make_tuple2(env,c_bin,d_bin);
	  return(tuple);
  }
  
  /*
  random_select for 3D-tensor data
  */
  static ERL_NIF_TERM
  random_select3(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
	  ErlNifBinary  a_bin,b_bin;
	  ERL_NIF_TERM  c_bin,d_bin,tuple;
	  int n1,h1,w1,r2,c2, i, j, k, n, r;
	  float *a, *b, *c, *d;
	
	  if (!enif_get_int(env, argv[0], &n1)) return enif_make_int(env,1);
	  if (!enif_get_int(env, argv[1], &h1)) return enif_make_int(env,2);
	  if (!enif_get_int(env, argv[2], &w1)) return enif_make_int(env,3);
	  if (!enif_inspect_binary(env, argv[3], &a_bin )) return enif_make_int(env,4);
	  if (!enif_get_int(env, argv[4], &r2)) return enif_make_int(env,5);
	  if (!enif_get_int(env, argv[5], &c2)) return enif_make_int(env,6);
	  if (!enif_inspect_binary(env, argv[6], &b_bin )) return enif_make_int(env,7);
	  if (!enif_get_int(env, argv[7], &n)) return enif_make_int(env,8);
  
	  a = (float *) a_bin.data;
	  b = (float *) b_bin.data;
	  c = (float *) enif_make_new_binary(env, n*h1*w1 * sizeof(float), &c_bin);
	  d = (float *) enif_make_new_binary(env, n*r2*c2 * sizeof(float), &d_bin);
  
	  // random-select
	  for(i=0;i<n;i++){
		  r = rand() % n1;
		  for(j=0;j<h1;j++){
			  for(k=0;k<w1;k++){
				  c[IDX3C(i,j,k,h1,w1)] = a[IDX3C(r,j,k,h1,w1)];
			  }
		  }
		  for(j=0;j<c2;j++){
			  d[IDX2C(i,j,n)] = b[IDX2C(r,j,r2)];
		  }    
	  }
  
	  tuple = enif_make_tuple2(env,c_bin,d_bin);
	  return(tuple);
  }
  
  
  
  static ERL_NIF_TERM
  is_near1(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
	  ErlNifBinary  a_bin,b_bin;
	  int i, n, sw;
	  float *a, *b;
	
	  if (!enif_get_int(env, argv[0], &n)) return enif_make_int(env,1);
	  if (!enif_inspect_binary(env, argv[1], &a_bin )) return enif_make_int(env,2);
	  if (!enif_inspect_binary(env, argv[2], &b_bin )) return enif_make_int(env,3);
  
	  a = (float *) a_bin.data;
	  b = (float *) b_bin.data;
  
	  // near check
	  sw = 0;
	  for(i=0;i<n;i++){
		 if(fabsf(a[i]) > fabsf(b[i])*1.15 || fabsf(a[i]) < fabsf(b[i])*0.85){
			  printf("%f %f \r\n", a[i], b[i]);
			  sw = 1;
		  }
	  }
	  if(sw == 0)
		  return enif_make_int(env,1); //true
	  else
		  return enif_make_int(env,0); //false
  }
  
  static ERL_NIF_TERM
  is_equal1(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
	  ErlNifBinary  a_bin,b_bin;
	  int i, n;
	  float *a, *b;
	
	  if (!enif_get_int(env, argv[0], &n)) return enif_make_int(env,1);
	  if (!enif_inspect_binary(env, argv[1], &a_bin )) return enif_make_int(env,2);
	  if (!enif_inspect_binary(env, argv[2], &b_bin )) return enif_make_int(env,3);
  
	  a = (float *) a_bin.data;
	  b = (float *) b_bin.data;
  
	  // equal check
	  for(i=0;i<n;i++){
		 if(a[i] != b[i]){
			  return enif_make_int(env,0); //false
		  }
	  }
	  
	  return enif_make_int(env,1); //true
  }
  
  
  
  static ERL_NIF_TERM
  analizer1(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
	  ErlNifBinary  a_bin;
	  int i, n, id;
	  float *a;
	  float max,min,sum;
	
	  if (!enif_get_int(env, argv[0], &n)) return enif_make_int(env,1);
	  if (!enif_inspect_binary(env, argv[1], &a_bin )) return enif_make_int(env,2);
	  if (!enif_get_int(env, argv[2], &id)) return enif_make_int(env,3);
  
	  a = (float *) a_bin.data;
  
	  // near check
	  for(i=0;i<n;i++){
		  if(isnan(a[i])){
			  return enif_make_int(env,9999);
		  }
		  if(isinf(a[i])){
			  return enif_make_int(env,9998);
		  }
	  }
  
	  //find max min avarage
	  max = -999999999;
	  min = 999999999;
	  sum = 0;
	  for(i=0;i<n;i++){
		  if(a[i] > max)
			  max = a[i];
		  
		  if(a[i] < min)
			  min = a[i];
		  
		  sum = sum+a[i];
  
	  }
	  printf("id max min average\r\n");
	  printf("%d %f %f %f \r\n", id, max, min, sum/(float)n);
  
	  return enif_make_int(env,1);
  }
  
  
  
	
	/*
	1st arg in_n of tensor
	2nd arg in_c of tensor
	3rd arg in_h of tensor
	4th arg in_w of tensor
	5th arg binary of tensor
	
	*/
  static ERL_NIF_TERM
  standardize1(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
	  ErlNifBinary  a_bin;
	  ERL_NIF_TERM  b_bin;
	  int in_n,in_c,in_h,in_w,n1,i,c1,h1,w1,count;
	  float *a,*b;
	  float sum,average;
	
	  if (!enif_get_int(env, argv[0], &in_n)) return enif_make_int(env,1);
	  if (!enif_get_int(env, argv[1], &in_c)) return enif_make_int(env,2);
	  if (!enif_get_int(env, argv[2], &in_h)) return enif_make_int(env,3);
	  if (!enif_get_int(env, argv[3], &in_w)) return enif_make_int(env,4);
	  if (!enif_inspect_binary(env, argv[4], &a_bin )) return enif_make_int(env,5);
  
	  n1 = in_n * in_c * in_h * in_w;
	  a = (float *) a_bin.data;
	  b = (float *) enif_make_new_binary(env, n1 * sizeof(float), &b_bin);
	 
	  
	  for(i=0;i<in_n;i++){
		  sum = 0.0;
		  for(c1=0;c1<in_c;c1++){
			  for(h1=0;h1<in_h;h1++){
				  for(w1=0;w1<in_w;w1++){
					  sum = sum + a[IDX4C(i,c1,h1,w1,in_c,in_h,in_w)];
				  }
			  }
		  }
		  count = in_c * in_h * in_w;
		  average = sum / (float)count;
		  for(c1=0;c1<in_c;c1++){
			  for(h1=0;h1<in_h;h1++){
				  for(w1=0;w1<in_w;w1++){
					  b[IDX4C(i,c1,h1,w1,in_c,in_h,in_w)] = a[IDX4C(i,c1,h1,w1,in_c,in_h,in_w)] - average;
				  }
			  }
		  }
	  }
	  
	  return(b_bin);
  }
  
  
	
  /*
  1st arg in_n of 3D tensor
  2rd arg in_r of 3D tensor
  3th arg in_c of 3D tensor
  4th arg binary of tensor
  5th arg nth in_r of 3D tensor
	
  */
  static ERL_NIF_TERM
  pickup1(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
	  ErlNifBinary  a_bin;
	  ERL_NIF_TERM  b_bin;
	  int in_n,in_row,in_col,nth,n1,i,j;
	  float *a,*b;
	  
	  if (!enif_get_int(env, argv[0], &in_n)) return enif_make_int(env,1);
	  if (!enif_get_int(env, argv[1], &in_row)) return enif_make_int(env,2);
	  if (!enif_get_int(env, argv[2], &in_col)) return enif_make_int(env,3);
	  if (!enif_inspect_binary(env, argv[3], &a_bin )) return enif_make_int(env,4);
	  if (!enif_get_int(env, argv[4], &nth)) return enif_make_int(env,5);
  
	  n1 = in_n * in_col;
	  a = (float *) a_bin.data;
	  b = (float *) enif_make_new_binary(env, n1 * sizeof(float), &b_bin);
	   
		
	  for(i=0;i<in_n;i++){
		  for(j=0;j<in_col;j++){
			  b[IDX2C(i,j,in_n)] = a[IDX3C(i,nth,j,in_row,in_col)];
		  }
	  }
		
	  return(b_bin);
  }
	
  
	
  /*
  1st arg size of tensor or matrix
  2rd arg binary of tensor or matrix
	
  */
  static ERL_NIF_TERM
  copy1(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
	  ErlNifBinary  a_bin;
	  ERL_NIF_TERM  b_bin;
	  int n,i;
	  float *a,*b;
	  
	  if (!enif_get_int(env, argv[0], &n)) return enif_make_int(env,1);
	  if (!enif_inspect_binary(env, argv[1], &a_bin )) return enif_make_int(env,2);
  
	  a = (float *) a_bin.data;
	  b = (float *) enif_make_new_binary(env, n * sizeof(float), &b_bin);
	   
		
	  for(i=0;i<n;i++){
		  b[i] = a[i];
	  }
		
	  return(b_bin);
  }
  
  
  static ERL_NIF_TERM
  slice1(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
	  ErlNifBinary  a_bin;
	  ERL_NIF_TERM  b_bin,c_bin,d_bin,e_bin,tuple;
	  int in_r,in_c,in_c1,i,j,n,bias;
	  float *a,*b,*c,*d,*e;
	  
	  if (!enif_get_int(env, argv[0], &in_r)) return enif_make_int(env,1);
	  if (!enif_get_int(env, argv[1], &in_c)) return enif_make_int(env,2);
	  if (!enif_inspect_binary(env, argv[2], &a_bin )) return enif_make_int(env,3);
  
	  in_c1 = in_c / 4;
	  n = in_r * (in_c / 4);
	  a = (float *) a_bin.data;
	  b = (float *) enif_make_new_binary(env, n * sizeof(float), &b_bin);
	  c = (float *) enif_make_new_binary(env, n * sizeof(float), &c_bin);
	  d = (float *) enif_make_new_binary(env, n * sizeof(float), &d_bin);
	  e = (float *) enif_make_new_binary(env, n * sizeof(float), &e_bin);
	   
		
	  for(i=0;i<in_r;i++){
		  for(j=0;j<in_c1;j++){
			  b[IDX2C(i,j,in_r)] = a[IDX2C(i,j,in_r)]; 
		  }
	  }
	  bias = in_c / 4;
	  for(i=0;i<in_r;i++){
		  for(j=0;j<in_c1;j++){
			  c[IDX2C(i,j,in_r)] = a[IDX2C(i,j+bias,in_r)]; 
		  }
	  }
	  bias = 2 * (in_c / 4);
	  for(i=0;i<in_r;i++){
		  for(j=0;j<in_c1;j++){
			  d[IDX2C(i,j,in_r)] = a[IDX2C(i,j+bias,in_r)]; 
		  }
	  }
	  bias = 3 * (in_c / 4);
	  for(i=0;i<in_r;i++){
		  for(j=0;j<in_c1;j++){
			  e[IDX2C(i,j,in_r)] = a[IDX2C(i,j+bias,in_r)]; 
		  }
	  }
		
	  tuple = enif_make_tuple4(env,b_bin,c_bin,d_bin,e_bin);
	  return(tuple);
  }
  
  static ERL_NIF_TERM
  unslice1(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
	  ErlNifBinary  b_bin,c_bin,d_bin,e_bin;
	  ERL_NIF_TERM  a_bin;
	  int in_r,in_c,i,j,n,bias;
	  float *a,*b,*c,*d,*e;
	  
	  if (!enif_get_int(env, argv[0], &in_r)) return enif_make_int(env,1);
	  if (!enif_get_int(env, argv[1], &in_c)) return enif_make_int(env,2);
	  if (!enif_inspect_binary(env, argv[2], &b_bin )) return enif_make_int(env,3);
	  if (!enif_inspect_binary(env, argv[3], &c_bin )) return enif_make_int(env,4);
	  if (!enif_inspect_binary(env, argv[4], &d_bin )) return enif_make_int(env,5);
	  if (!enif_inspect_binary(env, argv[5], &e_bin )) return enif_make_int(env,6);
  
	  n = in_r * in_c * 4;
	  a = (float *) enif_make_new_binary(env, n * sizeof(float), &a_bin);
	  b = (float *) b_bin.data;
	  c = (float *) c_bin.data;
	  d = (float *) d_bin.data;
	  e = (float *) e_bin.data;
	  
	  for(i=0;i<in_r;i++){
		  for(j=0;j<in_c;j++){
			  a[IDX2C(i,j,in_r)] = b[IDX2C(i,j,in_r)];
		  }
	  }
	  bias = in_c;
	  for(i=0;i<in_r;i++){
		  for(j=0;j<in_c;j++){
			  a[IDX2C(i,j+bias,in_r)] = c[IDX2C(i,j,in_r)]; 
		  }
	  }
	  bias = 2 * in_c;
	  for(i=0;i<in_r;i++){
		  for(j=0;j<in_c;j++){
			  a[IDX2C(i,j+bias,in_r)] = d[IDX2C(i,j,in_r)] ; 
		  }
	  }
	  bias = 3 * in_c;
	  for(i=0;i<in_r;i++){
		  for(j=0;j<in_c;j++){
			  a[IDX2C(i,j+bias,in_r)] = e[IDX2C(i,j,in_r)]; 
		  }
	  }
	  return(a_bin);
  }
  
  
  
  


*/