﻿using Lab05.BLL;
using System;
using System.Collections.Generic;
using Generic.Extensions;

Console.WriteLine("---------- zadanie 1 -----------");
Zoo zoo = new Zoo("Slaski ogrod zoologiczny",
    new List<Employee>(),
    new List<Cage>(),
    new List<Animal>());

Animal dog = new Mammal("flesh", 4, "Europe", "Gray Wolf", "Europe");


Animal cow = new Mammal("grass", 4, "Europe", "B. taurus", "Europe");

Animal crocodile1 = new Reptile("flesh", 4, "Africa", "C. niloticus", false);
Animal cobra = new Reptile("flesh", 0, "Africa", "Serpentes", true);

Cage cage1 = new Cage(4, false, new List<Animal> { dog, cow, crocodile1 });

Console.WriteLine(cage1);

Animal horse = new Mammal("Grass", 4, "North America, Europe", "E. ferus", "Europe");
Animal falcon = new Bird("flesh", 2, "Europe", "Falconidae", 1.2, 125);

(falcon as Bird).Fly();

Cage cage2 = new Cage(3, false, new List<Animal> { horse, falcon });
Console.WriteLine(cage2);

Cage cage3 = new Cage(10, false, new List<Animal>());
Console.WriteLine(cage3);

Cage cage4 = zoo.BuildCage(10, false);
zoo.ExpandCage(cage4, 5);


Employee emp1 = new Employee("Jakub", "Kowal", new DateTime(1999, 10, 15), new List<Cage> { cage1});

zoo.HireEmployee("adam", "kowalski", new DateTime(2000,2,4));
zoo.HireEmployee(emp1);

Console.WriteLine("=== ZOO ===");
Console.WriteLine(zoo);

Console.WriteLine("---------- zadanie 2 -----------");
//cage1.Print()
// Proszę dodać poniższe usingi na początku pliku

// Metoda Main



var cages1 = zoo.AddRange(new IList<Cage>() { cage1, cage2 }).Set<Cage>();
var cages2 = zoo.AddRange(new IList<Cage>()
    { cage3 }).Set<Cage>();
cages1.Print();
/*
Employee employee1 = new CageSupervisor("Jan", "Kowalski",
 new DateTime(1990, 1, 1), DateTime.Now, cages1);
Employee employee2 = new CageSupervisor("Adam", "Nowak",
 new DateTime(1988, 1, 1), DateTime.Now, cages2);
var newEmployee = zoo.HireEmployee("Robert", "Kowalczyk", new DateTime(1988, 1, 1));
var employees = zoo.AddRange(new List<Employee>()
{
employee1,
employee2
}).Set<Employee>();
((CageSupervisor)newEmployee).Add(cage4);
cage4.Add(cobra);
zoo.Add(cage4);
Console.WriteLine("+++++++++++++++++++++++++++++++++++++++");
Console.WriteLine();
dog.Print();
crocodile1.Print();
falcon.Print();
employees.Print();
zoo.Remove<Employee>(e => e.FirstName == "Adam" && e.LastName == "Nowak");
zoo.GetList<Employee>()
.Print();
cage1.Print();
cages2.Print();
Console.WriteLine("+++++++++++++++++++++++++++++++++++++++");
zoo.Print();
Console.WriteLine("+++++++++++++++++++++++++++++++++++++++");
zoo.Print();
*/