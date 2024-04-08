using Generic.Extensions;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;

namespace Lab05.BLL
{
    public class Employee : IContainer, IDisplayable
    {
        private string _firstName;
        private string _lastName;
        private DateTime _birthday;
        private IList<Cage> _cages;

        public Employee(string firstName, string lastName, DateTime birthday, IList<Cage> cage)
        {
            _firstName = firstName;
            _lastName = lastName;
            _birthday = birthday;
            _cages = cage;
        }


        public override string ToString()
        {
            string Str = "";
            foreach (var item in _cages)
            {
                Str += "\n   " + item.ToString();
            }
            return $"Employee | Firstname: {_firstName}, Lastname: {_lastName}, Birthday: {_birthday}, Cages: {Str}";
        }
    }
}