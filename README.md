# Ipod_Inventory_Problem

There is a company which have started selling the ipods ONLINE .But they want to sell these ipods online at best price.
-   They have ipod Inventories at Brazil and Argentina. Each of the inventory can store only 100 ipods.
-   ipods at Brazil are sold at 100$/unit and at Argentina they are sold at 50$/unit.
-   after every order the stock at both brazil and argentina inventories are again back to 100 units.
-   the no of ipods ordered should be only in multiple of 10.(i.e no of ipods ordered shouldnt be im number like 123 etc.)
-   the order placed should be either fullfilled completely or nothing
-   if the order is placed like 120 ipods from brazil then the remaining ipods can be brought from the other inventory    
    i.e.argentina. but here shipping price of 400$ per 10 units is applied.
    
4 set of inputs and outputs which your program should produce

#### INPUT-1
  Brazil : 5

#### OUTPUT-1
  500 : 95 : 100

#### INPUT-2
  Brazil : 50

#### OUTPUT-2
  4500 : 100 : 50
  (this trick here is u first have to calculate the cost price at both brazil and argentina..and d one which is low 
  should be given..here argentina)

#### INPUT-3
  Argentina : 120

#### OUTPUT-3
  7800 : 80 :20
  (this was the case where i made a silly mistake...out of 120 only 100 ipods should be sold according to the price at         argentina..while reamaining 20 should be sold at price at brazil which is 100$ + shipping charges (800$))

#### INPUT-4
  Argentina : 250

#### OUTPUT-4
  Out of stock!!!!
  
![2](https://user-images.githubusercontent.com/50991324/62243278-9d136280-b3fa-11e9-96eb-90f4257d3d89.png)
