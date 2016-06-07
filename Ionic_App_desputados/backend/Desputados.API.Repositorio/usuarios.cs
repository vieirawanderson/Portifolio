namespace Desputados.API.Repositorio
{
    using System;
    using System.Collections.Generic;
    using System.ComponentModel.DataAnnotations;
    using System.ComponentModel.DataAnnotations.Schema;
    using System.Data.Entity.Spatial;

    [Table("desputados.usuarios")]
    public partial class usuarios
    {
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Usage", "CA2214:DoNotCallOverridableMethodsInConstructors")]
        public usuarios()
        {
            ranking_usuario = new HashSet<ranking_usuario>();
        }

        public int ID { get; set; }

        [Required]
        [StringLength(200)]
        public string EMAIL { get; set; }

        [Required]
        [StringLength(300)]
        public string NOME { get; set; }

        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Usage", "CA2227:CollectionPropertiesShouldBeReadOnly")]
        public virtual ICollection<ranking_usuario> ranking_usuario { get; set; }
    }
}
