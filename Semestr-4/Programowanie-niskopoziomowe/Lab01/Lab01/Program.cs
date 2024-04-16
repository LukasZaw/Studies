Console.WriteLine("Hello, World!");

class Car
{
    private string _brand { get; set; }
    private string _model { get; set; }
    private int _doorCount { get; set; }
    private int _engineVolume { get; set; }
    private double _avgConsump { get; set; }

    static int _carCount = 0;

    public Car()
    {
        _brand = string.Empty;
        _model = string.Empty;
        _doorCount = 0;
        _engineVolume = 0;
        _avgConsump = 0;
        _carCount++;
    }

    public Car(string brand, string model, int _doorCount, int _engineVolume,  )


}

