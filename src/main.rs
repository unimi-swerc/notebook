use std::fs::{self, File};
use std::io::{self, Write};
use std::process::{exit, Command};

fn generate_code() -> Result<(), io::Error> {
    let mut code_file = File::create("build/code.tex")?;

    fs::read_dir("data")?
        .filter(Result::is_ok)
        .map(Result::unwrap)
        .map(|d| d.path())
        .filter(|p| p.is_dir())
        .map(|folder| -> Result<(), io::Error> {
            write!(
                code_file,
                "\\section{{{}}}\n",
                folder.file_name().and_then(|n| n.to_str()).unwrap(),
            )?;
            folder
                .read_dir()?
                .filter(Result::is_ok)
                .map(Result::unwrap)
                .map(|d| d.path())
                .filter(|p| p.is_file() && p.extension().and_then(|n| n.to_str()) == Some("cpp"))
                .map(|file| -> Result<(), io::Error> {
                    write!(
                        code_file,
                        "\\subsection{{{}}}\n\\code{{{}/{}}}\n",
                        file.file_stem().and_then(|n| n.to_str()).unwrap(),
                        folder.file_name().and_then(|n| n.to_str()).unwrap().replace(" ", "\\ "),
                        file.file_name().and_then(|n| n.to_str()).unwrap().replace(" ", "\\ "),
                    )
                })
                .collect()
        })
        .collect()
}

fn main() {
    if let Err(e) = fs::create_dir_all("build")
        .and_then(|_| File::create("build/swerc.tex"))
        .and_then(|mut f| f.write_all(include_bytes!("template.tex")))
        .and_then(|_| generate_code())
    {
        println!("Errore: {}", e);
        exit(1);
    }

    match Command::new("pdflatex")
        .current_dir("build")
        .arg("-halt-on-error")
        .arg("-shell-escape")
        .arg("swerc.tex")
        .spawn()
        .and_then(|mut c| c.wait())
    {
        Ok(c) => {
            let code = c.code().unwrap_or(0);
            if code != 0 {
                exit(code);
            }
        }
        Err(e) => {
            println!("Errore: {}", e);
            exit(1);
        }
    };
}
