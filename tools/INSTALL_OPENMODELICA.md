# Installing OpenModelica (the hard-gate compiler)

The hackathon's hard gate is: **the generated Modelica must compile in
OpenModelica.** This sets up `omc` so SpecAlive's `compile_check.py` can verify it.

## Windows (your machine)

1. **Download** the 64-bit installer from the official site:
   https://openmodelica.org/download/download-windows/
   (Pick the latest stable release, e.g. OpenModelica 1.24.x, 64-bit.)

2. **Run the installer.** Default location is
   `C:\Program Files\OpenModelica\`. Keep defaults; include the Modelica
   Standard Library (bundled).

3. **Verify** — open a *new* terminal and run:

   ```bash
   "C:\Program Files\OpenModelica\bin\omc.exe" --version
   ```

   You should see a version string (e.g. `OpenModelica 1.24.0`).

4. **(Optional) add to PATH** so you can just type `omc`:
   - Start → "Edit the system environment variables" → Environment Variables
   - Edit `Path` → New → `C:\Program Files\OpenModelica\bin`
   - Open a new terminal; `omc --version` should now work.

## Compile-check the L1 model

From `D:\SpecAlive`:

```bash
python tools/compile_check.py cases/tank/TwoTankController.mo
```

- If `omc` is on PATH it's found automatically; otherwise pass it explicitly:

```bash
python tools/compile_check.py cases/tank/TwoTankController.mo --omc "C:/Program Files/OpenModelica/bin/omc.exe"
```

- To also run the simulation (L1/L2 must simulate):

```bash
python tools/compile_check.py cases/tank/TwoTankController.mo --simulate
```

## What to do with the result

- **PASS** → the hard gate is satisfied for that model. 🎉
- **FAIL** → the tool prints the exact `omc` error text. **Paste that error back
  to me** and I'll fix the model — that's the model-repair loop, and it's a
  scored feature (PRD §5.2 "Model repair").

## GUI alternative (OMEdit)

OpenModelica also installs **OMEdit** (a graphical editor). You can
`File → Open` the `.mo`, and it will show check/simulate results and plots —
handy for eyeballing the tank-level trajectories during the demo.
