using Desputados.API.Repositorio;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Desputados.API.Models
{
    public class Alternativa
    {
        public int id { get; set; }

        public string descricao { get; set; }

        public bool alternativaCorreta { get; set; }

        public static implicit operator Alternativa(alternativas alternativas)
        {
            if (alternativas == null)
                return null;

            var a = new Alternativa();
            a.id = alternativas.ID;
            a.descricao = alternativas.DESCRICAO;
            a.alternativaCorreta = alternativas.CERTO;

            return a;
        }
    }
}
