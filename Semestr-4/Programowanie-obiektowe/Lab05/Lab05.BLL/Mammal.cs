using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Generic.Extensions;

namespace Lab05.BLL
{
    public class Mammal : Animal, IContainer, IDisplayable
    {
        private string _naturalEnvironment;

        public Mammal(string foodType, int legsCount, string origin, string species, string naturalEnv) 
            : base(foodType, legsCount, origin, species)
        {
            _naturalEnvironment = naturalEnv;
        }

        public override string ToString()
        {
            return base.ToString() + $"Natural Enviorment: {_naturalEnvironment}";
        }
    }
}