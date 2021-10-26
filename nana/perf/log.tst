printf("helloworld\n");
L("helloworld\n");
DL("helloworld\n");
gi = 0; LG(gi & 0x10, "helloworld\n");
gi = ~0; LG(gi & 0x10, "helloworld\n");
LHP(fprintf,log,"helloworld\n");
LHP(L_buffer_printf,buf,"helloworld\n");
LHP(syslog,LOG_USER,"helloworld\n");
