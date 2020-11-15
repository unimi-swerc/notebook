use clap::{App, AppSettings, SubCommand};
use rayon::prelude::*;
use std::fs::{self, File};
use std::io::{Error, ErrorKind, Write};
use std::path::Path;
use std::process::Command;

fn generate_code() -> Result<(), Error> {
    let mut code_file = File::create("build/code.tex")?;

    fs::read_dir("data")?
        .filter_map(|d| d.ok())
        .map(|d| d.path())
        .filter(|p| p.is_dir())
        .map(|folder| {
            write!(
                code_file,
                "\\section{{{}}}\n",
                folder.file_name().unwrap().to_string_lossy(),
            )?;
            folder
                .read_dir()?
                .filter_map(|d| d.ok())
                .map(|d| d.path())
                .filter(|p| {
                    p.is_file()
                        && p.extension().unwrap().to_string_lossy() == "cpp"
                        && !p.file_stem().unwrap().to_string_lossy().ends_with(".test")
                })
                .map(|file| {
                    write!(
                        code_file,
                        "\\subsection{{{}}}\n\\code{{{}/{}}}\n",
                        file.file_stem().unwrap().to_string_lossy(),
                        folder
                            .file_name()
                            .unwrap()
                            .to_string_lossy()
                            .replace(" ", "\\ "),
                        file.file_name()
                            .unwrap()
                            .to_string_lossy()
                            .replace(" ", "\\ "),
                    )
                })
                .collect()
        })
        .collect()
}

fn compile() -> Result<(), Error> {
    fs::create_dir_all("build")?;
    File::create("build/swerc.tex")?.write_all(include_bytes!("template.tex"))?;
    generate_code()?;

    let status = Command::new("pdflatex")
        .current_dir("build")
        .args(&["-halt-on-error", "-shell-escape", "swerc.tex"])
        .spawn()?
        .wait()?;

    if status.success() {
        Ok(())
    } else if let Some(code) = status.code() {
        Err(Error::new(
            ErrorKind::Other,
            format!("pdflatex failed with exit status {}", code),
        ))
    } else {
        Err(Error::new(ErrorKind::Other, "pdflatex failed"))
    }
}

fn test() -> Result<(), Error> {
    fs::create_dir_all("build-test")?;
    fs::read_dir("data")?
        .filter_map(|d| d.ok())
        .map(|d| d.path())
        .filter_map(|d| d.read_dir().ok())
        .flatten()
        .filter_map(|d| d.ok())
        .map(|d| d.path())
        .filter(|p| {
            p.is_file()
                && p.extension().unwrap().to_string_lossy() == "cpp"
                && !p.file_stem().unwrap().to_string_lossy().ends_with(".test")
        })
        .filter_map(|mut f| {
            f.set_extension("test.cpp");
            if f.exists() {
                Some(f)
            } else {
                println!(
                    "Warning: test file for \"{}\" not found",
                    f.file_stem().unwrap().to_string_lossy()
                );
                None
            }
        })
        .collect::<Vec<_>>()
        .par_iter()
        .map(|f| {
            println!("Compiling \"{}\"", f.file_stem().unwrap().to_string_lossy());
            let exe = Path::new("build-test/").join(f.file_stem().unwrap());
            let status = Command::new("g++")
                .arg("-std=c++17")
                .arg("-o")
                .arg(exe.clone())
                .arg(f)
                .spawn()?
                .wait()?;
            if !status.success() {
                return Err(Error::new(
                    ErrorKind::Other,
                    format!("g++ failed with exit status {}", status.code().unwrap_or(1)),
                ));
            }
            println!("Running \"{}\"", f.file_stem().unwrap().to_string_lossy());
            let status = Command::new(exe).spawn()?.wait()?;
            if !status.success() {
                Err(Error::new(
                    ErrorKind::Other,
                    format!(
                        "\"{}\" failed with exit status {}",
                        f.file_stem().unwrap().to_string_lossy(),
                        status.code().unwrap_or(1)
                    ),
                ))
            } else {
                println!("\"{}\" works!", f.file_stem().unwrap().to_string_lossy());
                Ok(())
            }
        })
        .collect::<Result<Vec<_>, Error>>()?;
    Ok(())
}

fn main() {
    let matches = App::new("swerc cheat-sheet generator")
        .version("0.1.0")
        .author("Alessandro Bortolin <bortolin.alessandro@outlook.it>")
        .setting(AppSettings::SubcommandRequired)
        .subcommand(SubCommand::with_name("compile"))
        .subcommand(SubCommand::with_name("test"))
        .get_matches();

    match match matches.subcommand_name() {
        Some("compile") => compile(),
        Some("test") => test(),
        _ => Ok(()),
    } {
        Ok(()) => {}
        Err(e) => println!("Error: {}", e),
    }
}
