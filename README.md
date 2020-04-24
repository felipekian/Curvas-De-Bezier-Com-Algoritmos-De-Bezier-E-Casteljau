# Curvas de Bézier com método da: equação paramétrica e Casteljau

---

## Intiução

_“Como criar uma curva que começa em um ponto, termina em outro, e a sua forma depende de pontos de controle, que irão “puxar” ou “afastar” a curva de suas proximidades?”._

Uma resposta plausível para esta questão seria que temos que construir uma função que estabeleça o “peso” que cada ponto de controle em cada momento ao longo da curva possa usar esses pesos para fazer a curva suavizar de acordo com o peso ou força que esse ponto de controle
exerce sobre a linha.

## Polinômio de Bernstein

Esse é o polinômio de Bernstein que foi usado por Bézier como base para construção da
curva. Onde (n i) é o polinômio de Newton, e o parâmetro x varia de 0 a 1.

![](Imagens_markdown/polinomio_bernstein.png)
