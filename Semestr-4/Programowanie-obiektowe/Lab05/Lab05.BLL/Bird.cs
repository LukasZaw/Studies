using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Generic.Extensions;

namespace Lab05.BLL
{
    public class Bird : Animal, IContainer, IDisplayable
    {
        private double _wingspan;
        private double _strength;

        

        public double Fly()
        {
            return _wingspan * _strength;
        }

        public Bird(string foodType, int legsCount, string origin, string species, double wingspan, double strength) 
            : base(foodType, legsCount, origin, species)
        {
            _wingspan = wingspan;
            _strength = strength;
        }

        public override string ToString()
        {
            return base.ToString() + $" Wing span: {_wingspan}, Strenght: {_strength}";
        }
    }
}