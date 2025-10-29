public class Candidat
    {
        public int codCandidat { get; set; }
        public string numeCandidat { get; set; }
        public float medieConcurs { get; set; }
        public int[] vectorOptiuni { get; set;  }

        public Candidat(int codCandidat, string numeCandidat, float medieConcurs, int[] vectorOptiuni)
        {
            this.codCandidat = codCandidat;
            this.numeCandidat = numeCandidat;
            this.medieConcurs = medieConcurs;
            this.vectorOptiuni = vectorOptiuni;
In formul principal,
public partial class lvPrograms : Form
{
        private List<ProgramStudiu> programs;
        public lvPrograms()
        {
            programs = new List<ProgramStudiu>();
            InitializeComponent();
        }

public void loadPrograms()
        {
            using(StreamReader reader =File.OpenText("ProgramStudii.txt"))
            {
                string line = null;
                while ((line = reader.ReadLine())!= null)
                {   var token = line.Split(',');
       var program = new ProgramStudiu(int.Parse(token[0]), token[1],       int.Parse(token[2]), int.Parse(token[3]));
                    programs.Add(program);
                }

public void afisarePrograme()
        {
            lvCandidats.Items.Clear();
            foreach(var r in programs)
            {
                ListViewItem item = new ListViewItem(r.codProgram.ToString());
                item.SubItems.Add(r.denumireProgram);
                item.SubItems.Add(r.numarlocuriBuget.ToString());
                item.SubItems.Add(r.numarLocurTaxa.ToString());
                item.Tag = r;
                lvCandidats.Items.Add(item);

private void lvPrograms_Load(object sender, EventArgs e)
        {
            loadPrograms();
            afisarePrograme();
        }

PrintDocument
public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            printDocument1.PrintPage += PrintDocument1_PrintPage;
        }

private void PrintDocument1_PrintPage(object sender,  System.Drawing.Printing.PrintPageEventArgs e)
        {
            Font font = new Font("Microsoft Sans Serif", 24);
            e.Graphics.DrawString("test", font, Brushes.Black, new Rectangle(0,0, 25,25));
        }

        private void button1_Click(object sender, EventArgs e)
        {
            printPreviewDialog1.ShowDialog();
        }
    }
