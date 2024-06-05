using Kolokwium.DAL.EF;
using Kolokwium.Model.Entities;
using Microsoft.EntityFrameworkCore;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;

namespace Kolokwium.WpfApp
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private readonly ApplicationDbContext _dbContext;

        public MainWindow(ApplicationDbContext dbContext)
        {

            _dbContext = dbContext;
            InitializeComponent();

        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            SetGrid(DataGridStudents, _dbContext.Students.Include(stud => stud.Grades));
        }


        private static void SetGrid<T>(DataGrid dataGrid, IEnumerable<T> list) where T : new()
        {
            dataGrid.Columns.Clear();
            var type = typeof(T);
            foreach (var prop in type.GetProperties())
                dataGrid.Columns.Add(new DataGridTextColumn()
                {
                    Header = prop.Name,
                    Binding = new Binding(prop.Name)
                });
            dataGrid.AutoGenerateColumns = false;
            dataGrid.ItemsSource = list;
            dataGrid.Items.Refresh();
        }

        private void ButtonAddEditStudentWindowShow_Click(object sender, RoutedEventArgs e)
        {
            Window1 addStudentWindow;
            if (DataGridStudents.SelectedItem != null && DataGridStudents.SelectedItem is Student student)
                addStudentWindow = new Window1(_dbContext, student);
            else
                addStudentWindow = new Window1(_dbContext);
            if (addStudentWindow.ShowDialog() == true)
                SetGrid(DataGridStudents, _dbContext.Students
                .Include(stud => stud.Grades));
        }
    }
}
