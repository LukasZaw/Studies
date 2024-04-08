using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Generic.Extensions;

namespace Lab05.BLL
{
    public class Cage : IContainer, IDisplayable
    {
        private int _capacity;
        private bool _clean;
        private IList<Animal> _animals;

        public Cage(int capacity, bool clean, IList<Animal> animals)
        {
            _capacity = capacity;
            _clean = clean;
            _animals = animals;
        }

        public void changeCapacity(int newCapacity)
        {
            _capacity = newCapacity;
        }

        public override string ToString()
        {
            string animalStr = "";
            foreach (var animal in _animals)
            {
                animalStr += "\n   " + animal.ToString();
            }
            return $"Cage | Capacity: {_capacity}, Cleaning: {_clean}, Animals: {animalStr}";
        }
    }
}