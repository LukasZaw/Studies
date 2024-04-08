using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Generic.Extensions;

namespace Lab05.BLL
{
    public class Reptile : Animal, IContainer, IDisplayable
    {
        private bool _venomous;

        public Reptile(string foodType, int legsCount, string origin, string species, bool venomus) 
            : base(foodType, legsCount, origin, species)
        {
            _venomous = venomus;
        }

        public override string ToString()
        {
            return base.ToString() + $"Venomous: {_venomous}";
        }
    }
}