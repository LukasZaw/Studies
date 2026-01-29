using kolos_WebAPI2.Models;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseHttpsRedirection();

var db = new List<Student>
{
    new Student { IdStudent = 1, FirstName = "John", LastName = "Doe", Age = 21 },
    new Student { IdStudent = 2, FirstName = "Jane", LastName = "Smith", Age = 22 },
    new Student { IdStudent = 3, FirstName = "Jim", LastName = "Beam", Age = 23 }
};

// GET /students
app.MapGet("/students", () =>
{
    return db;
});

// GET /students/{id}
app.MapGet("/students/{id}", (int id) =>
{
    var student = db.FirstOrDefault(s => s.IdStudent == id);
    return student is not null ? Results.Ok(student) : Results.NotFound();
});

// POST /students
app.MapPost("/students", (Student newStudent) =>
{
    newStudent.IdStudent = db.Max(s => s.IdStudent) + 1;
    db.Add(newStudent);
    return Results.Created($"/students/{newStudent.IdStudent}", newStudent);
});


// PUT /students/{id}
app.MapPut("/students/{id}", (int id, Student updatedStudent) =>
{
    var student = db.FirstOrDefault(s => s.IdStudent == id);
    if (student is null)
    {
        return Results.NotFound();
    }

    student.FirstName = updatedStudent.FirstName;
    student.LastName = updatedStudent.LastName;
    student.Age = updatedStudent.Age;

    return Results.NoContent();
});


// DELETE /students/{id}
app.MapDelete("/students/{id}", (int id) =>
{
    var student = db.FirstOrDefault(s => s.IdStudent == id);
    if (student is null)
    {
        return Results.NotFound();
    }

    db.Remove(student);
    return Results.Ok(student);
});

app.Run();
