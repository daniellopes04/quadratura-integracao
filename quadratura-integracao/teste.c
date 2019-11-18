 double func1(double x){

   return sin(pow(x,2));

 }

 simp simp_aux(double (*func) (double), double limiteA, double limiteB, double funcEmA, double funcEmB){

   double valorMedio, funcEmMedio, simpIntegral; double func1(double x){

   return sin(pow(x,2));

 }

 simp simp_aux(double (*func) (double), double limiteA, double limiteB, double funcEmA, double funcEmB){

   double valorMedio, funcEmMedio, simpIntegral;

   valorMedio = (limiteA + limiteB) / 2; //calcula o ponto médio
   funcEmMedio = func(valorMedio); //calcula a função avaliada no ponto médio

   simpIntegral = ( fabs(limiteB - limiteA) / 6 ) * (funcEmA + ( 4 * funcEmMedio ) + funcEmB); //calculo da integral pela regra de simpson

   simp values = {valorMedio, funcEmMedio, simpIntegral};

   return values;

 }

 double simp_adapt(double (*func) (double), double limiteA, double limiteB, double funcEmA, double funcEmB, double erroMaximo, double valorMedio, double funcEmMedio, double integral){   

   double delta;
   
   simp ladoEsquerdo = simp_aux(func, limiteA, valorMedio, funcEmA, funcEmMedio);
   simp ladoDireito = simp_aux(func, valorMedio, limiteB, funcEmMedio, funcEmB);

   delta = (ladoEsquerdo.simpIntegral + ladoDireito.simpIntegral) - integral;

   if ( fabs(delta) <= erro * 15 ) { return ladoDireito.simpIntegral + ladoEsquerdo.simpIntegral + (delta / 15); }

   return simp_adapt(func, limiteA, valorMedio, funcEmA, funcEmMedio, erro/2, ladoEsquerdo.valorMedio, ladoEsquerdo.funcEmMedio, ladoEsquerdo.simpIntegral) +
          simp_adapt(func, valorMedio, limiteB, funcEmMedio, funcEmB, erro/2, ladoDireito.valorMedio, ladoDireito.funcEmMedio, ladoDireito.simpIntegral);

 }

 double sim_inicio(double (*func) (double), double limiteA, double limiteB, double erro){

   double funcEmA = func(limiteA);
   double funcEmB = func(limiteB);

   simp values = simp_aux(func, limiteA, limiteB, funcEmA, funcEmB);

   return simp_adapt(func, limiteA, limiteB, funcEmA, funcEmB, erro, values.valorMedio, values.funcEmMedio, values.simpIntegral);

 }

   valorMedio = (limiteA + limiteB) / 2; //calcula o ponto médio
   funcEmMedio = func(valorMedio); //calcula a função avaliada no ponto médio

   simpIntegral = ( fabs(limiteB - limiteA) / 6 ) * (funcEmA + ( 4 * funcEmMedio ) + funcEmB); //calculo da integral pela regra de simpson

   simp values = {valorMedio, funcEmMedio, simpIntegral};

   return values;

 }

 double simp_adapt(double (*func) (double), double limiteA, double limiteB, double funcEmA, double funcEmB, double erroMaximo, double valorMedio, double funcEmMedio, double integral){   

   double delta;
   
   simp ladoEsquerdo = simp_aux(func, limiteA, valorMedio, funcEmA, funcEmMedio);
   simp ladoDireito = simp_aux(func, valorMedio, limiteB, funcEmMedio, funcEmB);

   delta = (ladoEsquerdo.simpIntegral + ladoDireito.simpIntegral) - integral;

   if ( fabs(delta) <= erro * 15 ) { return ladoDireito.simpIntegral + ladoEsquerdo.simpIntegral + (delta / 15); }

   return simp_adapt(func, limiteA, valorMedio, funcEmA, funcEmMedio, erro/2, ladoEsquerdo.valorMedio, ladoEsquerdo.funcEmMedio, ladoEsquerdo.simpIntegral) +
          simp_adapt(func, valorMedio, limiteB, funcEmMedio, funcEmB, erro/2, ladoDireito.valorMedio, ladoDireito.funcEmMedio, ladoDireito.simpIntegral);

 }

 double sim_inicio(double (*func) (double), double limiteA, double limiteB, double erro){

   double funcEmA = func(limiteA);
   double funcEmB = func(limiteB);

   simp values = simp_aux(func, limiteA, limiteB, funcEmA, funcEmB);

   return simp_adapt(func, limiteA, limiteB, funcEmA, funcEmB, erro, values.valorMedio, values.funcEmMedio, values.simpIntegral);

 }