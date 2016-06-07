namespace Desputados.API.Repositorio
{
    using System;
    using System.Collections.Generic;
    using System.ComponentModel.DataAnnotations;
    using System.ComponentModel.DataAnnotations.Schema;
    using System.Data.Entity.Spatial;

    [Table("desputados.ranking_usuario")]
    public partial class ranking_usuario
    {
        public int ID { get; set; }

        public int ID_USUARIO { get; set; }

        public int PONTUACAO { get; set; }

        public virtual usuarios usuarios { get; set; }
    }
}
