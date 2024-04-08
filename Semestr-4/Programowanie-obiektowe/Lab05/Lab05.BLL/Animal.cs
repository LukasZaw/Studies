using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Generic.Extensions;

namespace Lab05.BLL
{
    public class Animal : IContainer, IDisplayable
    {
        private string _foodType;
        private int _legsCount;
        private string _origin;
        private string _species;

        public Animal(string foodType, int legsCount, string origin, string species)
        {
            _foodType = foodType;
            _legsCount = legsCount;
            _origin = origin;
            _species = species;
        }

        public override string ToString()
        {
            return $"Animal | Food Type: {_foodType}, Legs: {_legsCount}, Origin: {_origin}, Species: {_species}, ";
        }
    }
}