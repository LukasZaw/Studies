using Generic.Extensions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


namespace Lab05.BLL
{
    public class Zoo : IContainer, IDisplayable
    {
        private string _name;
        private IList<Employee> _employees;
        private IList<Cage> _cages;
        private IList<Animal> _animals;

        public Zoo(string name, IList<Employee> employees, IList<Cage> cages, IList<Animal> animals)
        {
            _name = name;
            _employees = employees;
            _cages = cages;
            _animals = animals;
        }

        public Cage BuildCage(int capacity, bool clean)
        {
            return new Cage(capacity, clean, new List<Animal> { });
        }

        public void ExpandCage(Cage cage1, int newCapacity)
        {
            cage1.changeCapacity(newCapacity);
        }

        public void HireEmployee(string name, string lastname, DateTime dateTime)
        {
            _employees.Add(new Employee(name, lastname, dateTime, new List<Cage> { }));

        }

        public void HireEmployee(Employee emp)
        {
            _employees.Add(emp);

        }
        public override string ToString()
        {
            string EmpStr = "";
            foreach (var item in _employees)
            {
                EmpStr += "\n   " + item.ToString();
            }
            string CageStr = "";
            foreach (var item in _cages)
            {
                CageStr += "\n   " + item.ToString();
            }
            string AnimStr = "";
            foreach (var item in _animals)
            {
                AnimStr += "\n   " + item.ToString();
            }

            return $"ZOO || Name of Zoo: {_name}, Employees: {EmpStr}\n Cages: {CageStr}\n Animals: {AnimStr}\n";
        }
    }
}