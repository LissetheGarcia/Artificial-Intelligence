# Fuzzy Sets : 3D Surface Fitting Using a Takagi Sugeno Net and a Genetic Algorithm

# Used model

![image](https://user-images.githubusercontent.com/109912046/189814532-a92ee0cd-9616-4eaa-9be7-3a415213743a.png)

# Matlab/Octave example

      close all
      clear all

      m1=0;
      m2=0.5;
      m3=1;

      m4=0;
      m5=0.5;
      m6=1;

      de1=.21;
      de2=.21;
      de3=.21;

      de4=.21;
      de5=.21;
      de6=.21;

      p1=5;
      p2=0;
      p3=0;
      p4=0;
      p5=10;
      p6=0;
      p7=0;
      p8=0;
      p9=0;

      q1=5;
      q2=0;
      q3=0;
      q4=0;
      q5=300;
      q6=0;
      q7=0;
      q8=0;
      q9=0;

      r1=5;
      r2=0;
      r3=0;
      r4=0;
      r5=-100;
      r6=0;
      r7=0;
      r8=0;
      r9=0;


      for i=1:10,
      for j=1:10,

          x(i)=i/10;
          y(j)=j/10;

          mf1(i)=exp((-(x(i)-m1)^2)/(2*de1^2));
          mf2(i)=exp((-(x(i)-m2)^2)/(2*de2^2));
          mf3(i)=exp((-(x(i)-m3)^2)/(2*de3^2));

          mf4(j)=exp((-(y(j)-m4)^2)/(2*de4^2));
          mf5(j)=exp((-(y(j)-m5)^2)/(2*de5^2));
          mf6(j)=exp((-(y(j)-m6)^2)/(2*de6^2));

         inf1(i,j)=mf1(i)*mf4(j);
         inf2(i,j)=mf1(i)*mf5(j);
         inf3(i,j)=mf1(i)*mf6(j);
         inf4(i,j)=mf2(i)*mf4(j);
         inf5(i,j)=mf2(i)*mf5(j);
         inf6(i,j)=mf2(i)*mf6(j);
         inf7(i,j)=mf3(i)*mf4(j);
         inf8(i,j)=mf3(i)*mf5(j);
         inf9(i,j)=mf3(i)*mf6(j);

      reg1(i,j)=inf1(i,j)*((p1*x(i))+(q1*y(j))+r1);
      reg2(i,j)=inf2(i,j)*((p2*x(i))+(q2*y(j))+r2);
      reg3(i,j)=inf3(i,j)*((p3*x(i))+(q3*y(j))+r3);
      reg4(i,j)=inf4(i,j)*((p4*x(i))+(q4*y(j))+r4);
      reg5(i,j)=inf5(i,j)*((p5*x(i))+(q5*y(j))+r5);
      reg6(i,j)=inf6(i,j)*((p6*x(i))+(q6*y(j))+r6);
      reg7(i,j)=inf7(i,j)*((p7*x(i))+(q7*y(j))+r7);
      reg8(i,j)=inf8(i,j)*((p8*x(i))+(q8*y(j))+r8);
      reg9(i,j)=inf9(i,j)*((p9*x(i))+(q9*y(j))+r9);

      b(i,j)=inf1(i,j)+inf2(i,j)+inf3(i,j)+inf4(i,j)+inf5(i,j)+inf6(i,j)+inf7(i,j)+inf8(i,j)+inf9(i,j);
      a(i,j)=reg1(i,j)+reg2(i,j)+reg3(i,j)+reg4(i,j)+reg5(i,j)+reg6(i,j)+reg7(i,j)+reg8(i,j)+reg9(i,j);

      z(i,j)=a(i,j)/b(i,j);

      end
      end
      figure(1)
      surf(x,y,z)

      figure(2)
      plot(x,mf1,x,mf2,x,mf3)

      figure(3)
      plot(y,mf4,y,mf5,y,mf6)


![image](https://user-images.githubusercontent.com/109912046/189815132-5c7554bc-09cd-4c24-b250-01ddab060dfa.png)

'x' membership functions

![image](https://user-images.githubusercontent.com/109912046/189815208-7586b260-0e71-4684-bc89-1abfc46b2b9d.png)

'y' membership functions

![image](https://user-images.githubusercontent.com/109912046/189815253-8528e40a-88c9-45f5-974f-8808778703be.png)

