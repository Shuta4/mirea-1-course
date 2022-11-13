extern crate core;
use std::io;
use rand::Rng;

fn main() {
    let mut matrix = [[0u8; 8]; 8];
    let mut rng = rand::thread_rng();

    for i in &mut matrix {
        for j in &mut *i {
            *j = rng.gen_range(1..=100);
        }
    }

    let color = loop {
        let mut input = String::new();
        io::stdin()
            .read_line(&mut input)
            .expect("Failed to read line");
        let input = input.trim().to_lowercase();

        if input.eq("white") || input.eq("w") {
            break Some(Color::White);
        }
        else if input.eq("black") || input.eq("b") {
            break Some(Color::Black);
        }
        println!("{input} {}", input.eq("w"))
    };

    let color = match color {
        Some(color) => color,
        None => panic!(),
    };

    let mut result = [0u8; 32];
    let mut index: usize = 0;
    for i in 0..matrix.len() {
        for j in 0..matrix[i].len() {
            let is_white = i % 2 == 0 && j % 2 == 0
                || i % 2 != 0 && j % 2 != 0;

            if color == Color::White && is_white
                || color == Color::Black && !is_white {

                result[index] = matrix[i][j];
                index += 1;
            }
        }
    }

    quick_sort(&mut result);
    println!("{:?}", result)
}

fn quick_sort(slice: &mut [u8]) {
    if !slice.is_empty() {
        let partition_index = partition(slice);
        let len = slice.len();

        quick_sort(&mut slice[0..partition_index]);
        quick_sort(&mut slice[partition_index + 1..len]);
    }
}

fn partition(slice: &mut [u8]) -> usize {
    let len = slice.len();
    let pivot = slice[len - 1];
    let mut i = 0;
    let mut j = 0;

    while j < len - 1 {
        if slice[j] <= pivot {
            slice.swap(i, j);
            i += 1;
        }
        j += 1;
    }

    slice.swap(i, len - 1);

    i
}

#[derive(PartialEq)]
enum Color {
    Black, White
}