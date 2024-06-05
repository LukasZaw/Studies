using Kolokwium.DAL.EF;
using Kolokwium.Model.Entities;
using System.Windows;

namespace Kolokwium.WpfApp
{
    /// <summary>
    /// Logika interakcji dla klasy Window1.xaml
    /// </summary>
    public partial class Window1 : Window
    {
        private readonly Student? _student;
        private readonly ApplicationDbContext _dbContext;
        public Window1(ApplicationDbContext dbContext, Student student = null)
        {
            _dbContext = dbContext;
            DataContext = _student = student ?? new Student();
            InitializeComponent();
        }

        private void ButtonSaveStudent_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
