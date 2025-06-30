//TODO no exit, ele pega em qualquer numero (o valor)
// faz modulo talvez de 256, e assume o retorno
// 
/*
tfilipe-@c1r16s7:~$ bash
tfilipe-@c1r16s7:~$ exit 257
exit
tfilipe-@c1r16s7:~$ echo $?
1
tfilipe-@c1r16s7:~$ bash
tfilipe-@c1r16s7:~$ exit 258
exit
tfilipe-@c1r16s7:~$ echo $?
2
tfilipe-@c1r16s7:~$ bash
tfilipe-@c1r16s7:~$ exit 300
exit
tfilipe-@c1r16s7:~$ echo $?
44
tfilipe-@c1r16s7:~$ bash
tfilipe-@c1r16s7:~$ exit 256
exit
tfilipe-@c1r16s7:~$ echo $?
0
tfilipe-@c1r16s7:~$ bash
tfilipe-@c1r16s7:~$ exit 255
exit
tfilipe-@c1r16s7:~$ echo $?
255
*/