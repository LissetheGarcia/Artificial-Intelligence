# Evolutionary Computation : Curve Fitting using Genetic Algorithms

# Reference for the curve adjustment

This mathematical model could be changed to the desired one

A=8

B=25

C=4

D=45

E=10

F=17

G=35

for

i=1:1000,

x(i)=i/10;

y(i)=A*(B*sin(x(i)/C)+D*cos(x(i)/E))+F*x(i)-G ;

end

plot(x,y)

# 8 bits resolution chromosome

![image](https://user-images.githubusercontent.com/109912046/189811462-f3be9dbf-2278-4263-9d18-c8474e13037d.png)

# Tournament

Every chromosome is labeled with the aptitude function, then is randomly chosen a determined number of opponents, finally the best is selected.

![image](https://user-images.githubusercontent.com/109912046/189811740-347a1c61-da03-4269-89f6-003746028458.png)

# Reproduction

Crossover reproduction is applied.

![image](https://user-images.githubusercontent.com/109912046/189812012-64d3f720-1ff4-41f6-9190-f9d755a450ca.png)

# Mutation

Bit mutation is applied

![image](https://user-images.githubusercontent.com/109912046/189812124-08c9cd21-ab19-49ea-9066-c637e6dc59c7.png)

# Curve fitting video 

https://www.youtube.com/watch?v=jq6tjv3ECa4

