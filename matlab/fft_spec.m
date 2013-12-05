fid = fopen('t.data', 'rb');
t = fscanf(fid, '%f');

fid = fopen('f.data', 'rb');
f = fscanf(fid, '%f');

fid = fopen('fft.data', 'rb');
z = fscanf(fid, '%g');
z = reshape(z, length(f), real(length(z) / length(f)));

imagesc(t, f, z); axis xy; colormap(jet);