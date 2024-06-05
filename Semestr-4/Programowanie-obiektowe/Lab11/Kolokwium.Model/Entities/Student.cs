namespace Kolokwium.Model.Entities;
public class Student
{
    public int Id { get; set; }
    public long StudentIndex { get; set; }
    public string FirstName { get; set; } = null!;
    public string SurName { get; set; } = null!;
    public string Faculty { get; set; } = null!;
    public DateTime DateOfBirth { get; set; }
    public IList<Grade> Grades { get; set; } = null!; // właściwość nawigacyjna
    public string AllGrades => string.Join(", ", Grades);
}