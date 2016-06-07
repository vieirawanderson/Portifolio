namespace Desputados.API.Repositorio
{
    using System;
    using System.Collections.Generic;
    using System.ComponentModel.DataAnnotations;
    using System.ComponentModel.DataAnnotations.Schema;
    using System.Data.Entity.Spatial;

    [Table("desputados.alternativas")]
    public partial class alternativas
    {
        public int ID { get; set; }

        public int ID_QUESTAO { get; set; }

        [Required]
        [StringLength(3000)]
        public string DESCRICAO { get; set; }

        [Column(TypeName = "bit")]
        public bool CERTO { get; set; }

        public virtual questoes questoes { get; set; }
    }
}
