---
output: pdf_document
--- 

# 初等数论 计83李天勤2018080106

---

## Using markdown-memo to organize note paths

I did homework for this tab [[hw1.pdf]] it is pretty good application 

Using memo to create backlink: ![[backlink]]

Using cpp snippet


Embed photo ![[2022-03-28-11-05-56.png]]

---

## Using draw.io in vscode

![Image](test.drawio.svg)

---

Embed puml photo
<center> ![[out/sequences/sequences.png]] </center>

![[out/sequences/sequences.png]]


Using html with images
<center> ![Images](out/sequences/sequences.png) </center>


![Test Image](out/mindmap/example_mindmap.png)




Using align to center images
<div style="text-align:center">
  <img src="out/sequences/sequences.png" />
</div>

hello who are you

--- 
## Using UML within markdown
## uml: sequence diagram

```plantuml
@startuml
    skinparam backgroundColor #EEEBDC
    skinparam handwritten true
    actor Customer
    Customer -> "login()" : username & password
    "login()" -> Customer : session token
    activate "login()"
    Customer -> "placeOrder()" : session token, order info
    "placeOrder()" -> Customer : ok
    Customer -> "logout()"
    "logout()" -> Customer : ok
    deactivate "login()"
@enduml
```

# Hello 

This the best thing that I have done for this appliation
数据比较器
这是啥意思呢

type this thing is the best thing that I have done for this applicatoon
vscode is so op
        how do I know where to stop with this upgrading
        customer 
the best thing is that I know how to do the best typespeed is so fast 

数据选择器
这个挺好用的

```mermaid
graph TD;
    A-->B;
    A-->C;
    B-->D;
    C-->D
```

```mermaid
graph LR
A[Hard edge] -->B(Round edge)
    B --> C{Decision}
    C -->|One| D[Result one]
    C -->|Two| E[Result two]
```

```mermaid
graph LR
A[Hard edge] -->B(Round edge)
    B --> C{Decision}
    C -->|One| D[Result one]
    C -->|Two| E[Result two]
```
```mermaid
classDiagram
      Animal <|-- Duck
      Animal <|-- Fish
      Animal <|-- Zebra
      Animal : +int age
      Animal : +String gender
      Animal: +isMammal()
      Animal: +mate()
      class Duck{
          +String beakColor
          +swim()
          +quack()
      }
      class Fish{
          -int sizeInFeet
          -canEat()
      }
      class Zebra{
          +bool is_wild
          +run()
      }
```

```mermaid
pie
    title Pie Chart
    "Dogs" : 386
    "Cats" : 85
    "Rats" : 150 
```

```mermaid
%% Example of sequence diagram
  sequenceDiagram
    Alice->>Bob: Hello Bob, how are you?
    alt is sick
    Bob->>Alice: Not so good :(
    else is well
    Bob->>Alice: Feeling fresh like a daisy
    end
    opt Extra response
    Bob->>Alice: Thanks for asking
    end
```

<!-- <center>  -->

# uml: class diagram
![Classes](out/classes/classes.png)




# Math
$$ \begin{pmatrix} 0 \\ 0 \\ 0 \end{pmatrix} $$ 
$$ \begin{bmatrix} 0 \\ 0 \\ 0 \end{bmatrix} $$
$$ \sum_{i=1}^n X_i $$

Therefore the solution is $a$, 
$$ x = \begin{cases} 1 \\ 2 \\ 3 \end{cases} $$

$$  
\begin{darray}{rlr}
x^2 y'' - xy &= 0\\
\end{darray}  
$$

```python
print('hello world')
for element in elements:
    print(elements.first())

```


$$ \begin{vmatrix}
\end{vmatrix} $$

