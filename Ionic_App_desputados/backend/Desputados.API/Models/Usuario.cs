using Desputados.API.Repositorio;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Desputados.API.Models
{
    public class Usuario
    {
        public int? id { get; set; }

        public string nome { get; set; }

        public string email { get; set; }

        public static implicit operator Usuario(usuarios usuario)
        {
            if (usuario == null)
                return null;

            return new Usuario()
            {
                id = usuario.ID,
                nome = usuario.NOME,
                email = usuario.EMAIL
            };
        }
    }
}
