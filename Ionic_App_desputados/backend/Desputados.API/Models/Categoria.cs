using Desputados.API.Repositorio;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Desputados.API.Models
{
    public class Categoria
    {
        public int id { get; set; }

        public string descricao { get; set; }

        public static implicit operator Categoria(categorias categoria)
        {
            if (categoria == null)
                return null;

            return new Categoria()
            {
                descricao = categoria.DESCRICAO,
                id = categoria.ID
            };
        }
    }
}
