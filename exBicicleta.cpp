Clasa Bicicleta
    [Serializable]
    public class Bicicleta
    {
        public int CodB;
        public string StatieParcare { get; set; }
        public int KmParcursi { get; set; }

        public Bicicleta(int codB, string statieParcare, int kmParcursi)
        {
            CodB = codB;
            StatieParcare = statieParcare;
            KmParcursi = kmParcursi;
        }
    }
Clasa Utilizator
{
    [Serializable]
    public class Utilizator
    {
        public string Nume { get; set; }
        public int CodB { get; set; }
        public int DurataUtilizare { get; set; }

        public Utilizator(string nume, int codB, int durataUtilizare)
        {
            Nume = nume;
            CodB = codB;
            DurataUtilizare = durataUtilizare;
        }
    }

PROGRAM.CS
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
FORM1
    public partial class Form1 : Form
    {
        int sum = 0;
        List<Bicicleta> biciclete = new List<Bicicleta>();
        List<Utilizator> utilizatori = new List<Utilizator>();
        public Form1()
        {
            InitializeComponent();
            BicicleteDinFisier();
            afisareBicicleteLV();
            UtilizatoriDinFisier();
            afisareUtilizatoriLV();
        }

        void BicicleteDinFisier()
        {
            using(StreamReader file=new StreamReader("biciclete.txt"))
            {
                int nrBiciclete = int.Parse(file.ReadLine());
                for(int i=0;i<nrBiciclete;i++)
                {
                    int codB = int.Parse(file.ReadLine());
                    string statieParcare = file.ReadLine();
                    int kmParcursi = int.Parse(file.ReadLine());

                    Bicicleta bicicleta = new Bicicleta(codB, statieParcare, kmParcursi);
                    biciclete.Add(bicicleta);
                }
            }
        }

        void afisareBicicleteLV()
        {
            lvBiciclete.Items.Clear();
            foreach(Bicicleta b in biciclete)
            {
                ListViewItem item = new ListViewItem(b.CodB.ToString());
                item.SubItems.Add(b.StatieParcare);
                item.SubItems.Add(b.KmParcursi.ToString());

                item.Tag = b;
                lvBiciclete.Items.Add(item);

            }
        }
        void UtilizatoriDinFisier()
        {
            using(StreamReader file=new StreamReader("utilizatori.txt"))
            {
                int nrUtilizatori = int.Parse(file.ReadLine());
                for(int i=0;i<nrUtilizatori;i++)
                {
                    string nume = file.ReadLine();
                    int codB = int.Parse(file.ReadLine());
                    int durataUtilizare = int.Parse(file.ReadLine());

                    Utilizator utilizator = new Utilizator(nume, codB, durataUtilizare);
                    utilizatori.Add(utilizator);
                }
            }
        }
        void afisareUtilizatoriLV()
        {
            lvUtilizatori.Items.Clear();
            foreach(Utilizator u in utilizatori)
            {
                ListViewItem item = new ListViewItem(u.Nume);
                item.SubItems.Add(u.CodB.ToString());
                item.SubItems.Add(u.DurataUtilizare.ToString());

                item.Tag = u;
                lvUtilizatori.Items.Add(item);
            }
        }

        private void btnEdit_Click(object sender, EventArgs e)
        {
            if(lvUtilizatori.SelectedItems.Count==0)
            {
                MessageBox.Show("Selectati un utilizator!", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            else
            {
                ListViewItem listViewItem = lvUtilizatori.SelectedItems[0];
                Utilizator utilizator = (Utilizator)listViewItem.Tag;

                EditForm form = new EditForm(utilizator);
                if(form.ShowDialog()==DialogResult.OK)
                {
                    afisareUtilizatoriLV();
                }
            }
        }

        private void btnCalculeaza_Click(object sender, EventArgs e)
        {
            
            if(lvBiciclete.SelectedItems.Count==0)
            {
                MessageBox.Show("Selectati o bicicleta!", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            else
            {
                ListViewItem item = lvBiciclete.SelectedItems[0];
                Bicicleta bicicleta = (Bicicleta)item.Tag;

                foreach(Utilizator utilizator in utilizatori)
                {
                    if(utilizator.CodB==bicicleta.CodB)
                    {
                        if(utilizator.DurataUtilizare>30)
                        {
                            sum += ((utilizator.DurataUtilizare - 30) / 10)*2;
                        }
                    }
                }
                tbSuma.Text = sum.ToString();
            }
        }

        private void btnSerializare_Click(object sender, EventArgs e)
        {
            BinaryFormatter formatter = new BinaryFormatter();
            using (FileStream file = File.Create("biciclete.dat"))
            {
                formatter.Serialize(file, biciclete);
            }
            using(FileStream file=File.Create("utilizatori.dat"))
            {
                formatter.Serialize(file, utilizatori);
            }
        }

        private void btnDeserializare_Click(object sender, EventArgs e)
        {
            BinaryFormatter formatter = new BinaryFormatter();
            using(FileStream file=File.OpenRead("biciclete.dat"))
            {
                biciclete = (List<Bicicleta>)formatter.Deserialize(file);
                afisareBicicleteLV();
            }
            using (FileStream file = File.OpenRead("utilizatori.dat"))
            {
                utilizatori = (List<Utilizator>)formatter.Deserialize(file);
                afisareUtilizatoriLV();
            }
        }

EDIT FORM
   public partial class EditForm : Form
    {
        Utilizator utilizator;
        public EditForm(Utilizator u)
        {
            utilizator = u;
            InitializeComponent();
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            utilizator.Nume = tbName.Text;
            utilizator.CodB = (int)nudCodB.Value;
            utilizator.DurataUtilizare = (int)nudDurataUtilizare.Value;
        }

        private void tbName_Validating(object sender, CancelEventArgs e)
        {
            if(tbName.Text.Trim().Length<3)
            {
                errorProvider1.SetError(tbName, "Lungimea minima este 3!");
            }
            else
            {
                errorProvider1.SetError(tbName, null);
            }
        }

        private void nudCodB_Validating(object sender, CancelEventArgs e)
        {
            if(nudCodB.Value<=0)
            {
                errorProvider1.SetError(nudCodB, "Codul este invalid!");
            }
            else
            {
                errorProvider1.SetError(nudCodB, null);
            }
        }

        private void nudDurataUtilizare_Validating(object sender, CancelEventArgs e)
        {
            if(nudDurataUtilizare.Value<10)
            {
                errorProvider1.SetError(nudDurataUtilizare, "Durata este prea scurta!");
            }
            else
            {
                errorProvider1.SetError(nudDurataUtilizare, null);
            }
        }
    }
}

