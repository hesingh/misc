```c
apply {
   pkt_filter4.apply();
   intermediate_upf_filter.apply();
   /* rest of code */
}

Change to:

apply {
   pkt_filter4.apply();
   /* rest of code */
}

apply {
   intermediate_upf_filter.apply();
   /* rest of code */
}
///////////////////////////////////
apply {
   /* code block 1 */
   if () {

   } else {
       pkt_filter4.apply();
       intermediate_upf_filter.apply();
   }
}

Change to:

apply {
   /* code block 1 */
   if () {

   } else {
       pkt_filter4.apply();
   }
}

apply {
   /* code block 1 */
   if () {

   } else {
       intermediate_upf_filter.apply();
   }
}
////////////////////////////////////
apply {
   /* code block 1 */
   if () {
       pkt_filter4.apply();
       intermediate_upf_filter.apply();
   } else {
     ;
   }
}

Change to:

apply {
   /* code block 1 */
   if () {
       pkt_filter4.apply();
   } else {
     ;
   }
}

apply {
   /* code block 1 */
   if () {
       intermediate_upf_filter.apply();
   } else {
     ;
   }
}
```
