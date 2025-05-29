import 'package:flutter/material.dart';

void main() {
  runApp(TaskApp());
}

//Klasa Zadania
class Task {
  String name;
  String description;
  DateTime startDate;
  int priority;

  Task({
    required this.name,
    required this.description,
    required this.startDate,
    required this.priority,
  });
}

class TaskApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Zarządzanie Zadaniami',
      theme: ThemeData(
        primarySwatch: Colors.deepPurple,
      ),
      home: TaskListScreen(),
    );
  }
}


//Widok Główny
class TaskListScreen extends StatefulWidget {
  @override
  _TaskListScreenState createState() => _TaskListScreenState();
}

class _TaskListScreenState extends State<TaskListScreen> {
  List<Task> tasks = [];

  @override
  void initState() {
    super.initState();
    tasks = [
      Task(
        name: 'Nauka Fluttera',
        description: 'Kurs Flutter na Youtube',
        startDate: DateTime.now().subtract(Duration(days: 1)),
        priority: 2,
      ),
      Task(
        name: 'Zakupy spożywcze',
        description: 'Kupić mleko, chleb i jajka',
        startDate: DateTime.now(),
        priority: 1,
      ),
      Task(
        name: 'Spotkanie z zespołem',
        description: 'Omówienie projektu aplikacji',
        startDate: DateTime.now().add(Duration(days: 2)),
        priority: 3,
      ),
    ];
  }


  void _addOrEditTask({Task? task, int? index}) async {
    final result = await Navigator.push(
      context,
      MaterialPageRoute(
        builder: (context) => TaskDetailScreen(task: task),
      ),
    );

    if (result != null && result is Task) {
      setState(() {
        if (index == null) {
          tasks.add(result);
        } else {
          tasks[index] = result;
        }
      });
    }
  }

  void _deleteTask(int index) {
    setState(() {
      tasks.removeAt(index);
    });
  }

  Color _getPriorityColor(int priority) {
    switch (priority) {
      case 1:
        return Colors.green.shade100; // Low priority (green)
      case 2:
        return Colors.orange.shade100; // Medium priority (orange)
      case 3:
        return Colors.red.shade100; // High priority (red)
      default:
        return Colors.white;
    }
  }

  String _formatDate(DateTime date) {
    return "${date.day}-${date.month}-${date.year}"; // Format: dd-MM-yyyy
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Lista Zadań'),
      ),
      body: ListView.builder(
        itemCount: tasks.length,
        itemBuilder: (context, index) {
          final task = tasks[index];
          return Container(
            color: _getPriorityColor(task.priority),
            child: ListTile(
              title: Text(task.name),
              subtitle: Text('Priorytet: ${task.priority}\nData: ${_formatDate(task.startDate)}'),
              onTap: () {
                Navigator.push(
                  context,
                  MaterialPageRoute(
                    builder: (context) => TaskViewScreen(
                      task: task,
                      index: index,
                      onEdit: (updatedTask, idx) {
                        setState(() {
                          tasks[idx] = updatedTask;
                        });
                      },
                    ),
                  ),
                );
              },

              trailing: IconButton(
                icon: Icon(Icons.delete, color: Colors.red),
                onPressed: () => _deleteTask(index),
              ),
            ),
          );
        },
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: () => _addOrEditTask(),
        child: Icon(Icons.add),
      ),
    );
  }
}


//Widok szczegółów zadania
class TaskViewScreen extends StatelessWidget {
  final Task task;
  final int index;
  final void Function(Task updatedTask, int index) onEdit;

  TaskViewScreen({
    required this.task,
    required this.index,
    required this.onEdit,
  });

  String _formatDate(DateTime date) {
    return "${date.day.toString().padLeft(2, '0')}-${date.month.toString().padLeft(2, '0')}-${date.year}";
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: Text('Szczegóły Zadania')),
      body: SingleChildScrollView(
        child: Padding(
          padding: const EdgeInsets.all(12.0),
          child: Card(
            elevation: 8,
            shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(25)),
            child: Padding(
              padding: const EdgeInsets.all(16.0),
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  Center(
                    child: Text(
                      task.name,
                      style: TextStyle(fontSize: 30, fontWeight: FontWeight.bold),
                      textAlign: TextAlign.center,
                    ),
                  ),
                  SizedBox(height: 20),
                  Row(
                    children: [
                      Icon(Icons.description, color: Colors.green),
                      SizedBox(width: 10),
                      Expanded(
                        child: Text(
                          task.description.isNotEmpty
                              ? task.description
                              : 'Brak opisu',
                          style: TextStyle(fontSize: 20),
                        ),
                      ),
                    ],
                  ),
                  SizedBox(height: 15),
                  Row(
                    children: [
                      Icon(Icons.calendar_today, color: Colors.green),
                      SizedBox(width: 10),
                      Text(
                        'Data: ${_formatDate(task.startDate)}',
                        style: TextStyle(fontSize: 16),
                      ),
                    ],
                  ),
                  SizedBox(height: 15),
                  Row(
                    children: [
                      Icon(Icons.priority_high, color: Colors.green),
                      SizedBox(width: 10),
                      Text(
                        'Priorytet: ${task.priority}',
                        style: TextStyle(fontSize: 16),
                      ),
                    ],
                  ),
                  SizedBox(height: 34),
                  Center(
                    child: ElevatedButton.icon(
                      onPressed: () async {
                        final updatedTask = await Navigator.push(
                          context,
                          MaterialPageRoute(
                            builder: (context) => TaskDetailScreen(task: task),
                          ),
                        );
                        if (updatedTask != null && updatedTask is Task) {
                          onEdit(updatedTask, index);
                          Navigator.pop(context);
                        }
                      },
                      icon: Icon(Icons.edit, color: Colors.lightGreen[800]),
                      label: Text('Edytuj Zadanie'),
                      style: ElevatedButton.styleFrom(
                        padding: EdgeInsets.symmetric(horizontal: 20, vertical: 12),
                        shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(10)),
                      ),
                    ),
                  ),
                ],
              ),
            ),
          ),
        ),
      ),
    );
  }
}




class TaskDetailScreen extends StatefulWidget {
  final Task? task;

  TaskDetailScreen({this.task});

  @override
  _TaskDetailScreenState createState() => _TaskDetailScreenState();
}

class _TaskDetailScreenState extends State<TaskDetailScreen> {
  final _formKey = GlobalKey<FormState>();
  late TextEditingController _nameController;
  late TextEditingController _descriptionController;
  DateTime _startDate = DateTime.now();
  int _priority = 1;

  @override
  void initState() {
    super.initState();
    _nameController =
        TextEditingController(text: widget.task?.name ?? '');
    _descriptionController =
        TextEditingController(text: widget.task?.description ?? '');
    _startDate = widget.task?.startDate ?? DateTime.now();
    _priority = widget.task?.priority ?? 1;
  }

  void _saveTask() {
    if (_formKey.currentState!.validate()) {
      final newTask = Task(
        name: _nameController.text,
        description: _descriptionController.text,
        startDate: _startDate,
        priority: _priority,
      );
      Navigator.pop(context, newTask);
    }
  }

  Future<void> _pickDate() async {
    final picked = await showDatePicker(
      context: context,
      initialDate: _startDate,
      firstDate: DateTime(2000),
      lastDate: DateTime(2100),
    );
    if (picked != null) {
      setState(() {
        _startDate = picked;
      });
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.task == null ? 'Dodaj Zadanie' : 'Edytuj Zadanie'),
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Form(
          key: _formKey,
          child: Column(
            children: [
              TextFormField(
                controller: _nameController,
                decoration: InputDecoration(labelText: 'Nazwa zadania'),
                validator: (value) =>
                value == null || value.isEmpty ? 'Wprowadź nazwę' : null,
              ),
              TextFormField(
                controller: _descriptionController,
                decoration: InputDecoration(labelText: 'Opis'),
              ),
              Row(
                children: [
                  Expanded(
                    child: Text(
                      'Data rozpoczęcia: ${_startDate.toLocal()}'.split(' ')[0],
                    ),
                  ),
                  TextButton(
                    onPressed: _pickDate,
                    child: Text('Wybierz datę'),
                  ),
                ],
              ),
              DropdownButtonFormField<int>(
                value: _priority,
                items: [1, 2, 3]
                    .map((e) => DropdownMenuItem(
                  value: e,
                  child: Text('Priorytet - $e'),
                ))
                    .toList(),
                onChanged: (value) {
                  setState(() {
                    _priority = value!;
                  });
                },
                decoration: InputDecoration(labelText: 'Priorytet zadania:'),
              ),
              SizedBox(height: 50),
              ElevatedButton(
                onPressed: _saveTask,
                child: Text('Zapisz'),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
