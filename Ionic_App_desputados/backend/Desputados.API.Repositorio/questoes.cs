namespace Desputados.API.Repositorio
{
    using System;
    using System.Collections.Generic;
    using System.ComponentModel.DataAnnotations;
    using System.ComponentModel.DataAnnotations.Schema;
    using System.Data.Entity.Spatial;

    [Table("desputados.questoes")]
    public partial class questoes
    {
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Usage", "CA2214:DoNotCallOverridableMethodsInConstructors")]
        public questoes()
        {
            alternativas = new HashSet<alternativas>();
        }

        public int ID { get; set; }

        public int ID_CATEGORIA { get; set; }

        [Required]
        [StringLength(3000)]
        public string ENUNCIADO { get; set; }

        [StringLength(3000)]
        public string RESOLUCAO { get; set; }

        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Usage", "CA2227:CollectionPropertiesShouldBeReadOnly")]
        public virtual ICollection<alternativas> alternativas { get; set; }

        public virtual categorias categorias { get; set; }
    }
}
